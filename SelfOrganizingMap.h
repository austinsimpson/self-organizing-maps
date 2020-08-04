#ifndef SELFORGANIZINGMAP_H
#define SELFORGANIZINGMAP_H

#include <QVector>

#include "VectorND.h"
#include "SelfOrganizingMapCategory.h"
#include "SelfOrganizingMapUnit.h"

#include <random>
#include <numeric>

constexpr auto kInitialEta = .20;

template <int Dimension>
class SelfOrganizingMap
{
public:
    SelfOrganizingMap(size_t gridLength): _initialSigma(0.5 * sqrt(gridLength)), _gridLength(gridLength), _numberOfIterations(1000)
    {

    }

    void train()
    {
        initializeGrid();
        for (const auto index : range(0, _numberOfIterations))
        {
            iterate(index);
        }

        generateCategories();
    }

    void trainWithCallback(std::function<void(const QVector<SelfOrganizingMapUnit<Dimension>>&, const int)> callback)
    {
        for (const auto iterationNumber : range(0, 1000))
        {
            iterate(iterationNumber);
            callback(_grid, iterationNumber);
        }
    }

    void iterate(int iterationsSoFar)
    {
        auto index = _indexDistribution(_generator);
        const VectorND<Dimension>& currentTrainingPoint = _trainingPoints[index];
        const auto& bestMatchingUnit = findBestMatchingUnit(currentTrainingPoint);
        for (auto& unit : _grid)
        {
            const qreal distance = (bestMatchingUnit.position() - unit.position()).lengthSquared();
            const qreal currentLearningRate = learningRate(distance, iterationsSoFar);
            if (std::isnan(currentLearningRate) == false)
            {
                const VectorND<Dimension> vec = (currentTrainingPoint - unit.value());
                unit.value() += (currentTrainingPoint - unit.value()) * currentLearningRate;
            }
        }
    }

    void setTrainingPoints(const QVector<VectorND<Dimension>>& trainingPoints)
    {
        _trainingPoints = trainingPoints;
        _indexDistribution = std::uniform_int_distribution<int>(0, trainingPoints.count() - 1);
    }

    const QVector<VectorND<Dimension>>& trainingPoints() const
    {
        return _trainingPoints;
    }

    const QVector<SelfOrganizingMapCategory<Dimension>>& categories() const
    {
        return _categories;
    }

    const QVector<SelfOrganizingMapUnit<Dimension>>& grid() const
    {
        return _grid;
    }

    const SelfOrganizingMapUnit<Dimension>& findBestMatchingUnit(const VectorND<Dimension>& inputVector) const
    {
        return *std::min_element(_grid.begin(), _grid.end(), [inputVector](const auto& firstUnit, const auto& secondUnit)
        {
            const auto& firstDifference = (inputVector - firstUnit.value()).lengthSquared();
            const auto& secondDifference = (inputVector - secondUnit.value()).lengthSquared();
            return firstDifference < secondDifference;
        });
    }

    void setGridLength(size_t gridLength)
    {
        _gridLength = gridLength;
        _initialSigma = 0.5 * sqrt(gridLength);
    }

    void setNumberOfIterations(size_t iterations)
    {
        _numberOfIterations = iterations;
    }

private:
    void initializeGrid()
    {
        std::uniform_real_distribution<qreal> samplingDistribution(0.0, 1.0);

        for (auto row : range(0, _gridLength))
        {
            for (auto column : range(0, _gridLength))
            {
                VectorND<Dimension> randomVector;
                for (auto i : range(0, Dimension))
                {
                    randomVector[i] = samplingDistribution(_generator);
                }
                const auto x = static_cast<double>(column);
                const auto y = static_cast<double>(row);
                _grid.push_back(SelfOrganizingMapUnit<Dimension>(randomVector, { x, y }));
            }
        }
    }

    qreal learningRate(qreal distanceSquared, int iterationCount)
    {
        const auto timeDecay = exp(-1.0 * iterationCount / 200.0);
        const auto eta = kInitialEta * timeDecay;
        const auto sigma = _initialSigma * timeDecay;
        return eta * exp(-distanceSquared / (2. * sigma * sigma));

    }

    void generateCategories()
    {
        _categories.clear();
        for (const auto index: range(0, _grid.size()))
        {
            const auto y = static_cast<qreal>(index) / _gridLength;
            const auto x = static_cast<qreal>(index % _gridLength);

            _categories.push_back(SelfOrganizingMapCategory<Dimension>(_grid[index]));
        }

        for (const auto trainingPoint: _trainingPoints)
        {
            const auto& bestMatchingUnit = findBestMatchingUnit(trainingPoint);
            const int index = bestMatchingUnit.position()[0] + _gridLength * bestMatchingUnit.position()[1];
            _categories[index].items().append(trainingPoint);
        }
    }

    size_t _gridLength;
    qreal _initialSigma;
    size_t _numberOfIterations;

    QVector<VectorND<Dimension>> _trainingPoints;
    QVector<SelfOrganizingMapUnit<Dimension>> _grid;
    QVector<SelfOrganizingMapCategory<Dimension>> _categories;

    std::uniform_int_distribution<int> _indexDistribution;
    std::default_random_engine _generator;
};

#endif // SELFORGANIZINGMAP_H
