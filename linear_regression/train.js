const csv = require('./csv')
const nodeplotlib = require('nodeplotlib')
const yargs = require('yargs')

const argv = yargs.option('plot', {
    description: 'Plot linear regression on a chart',
    type: 'boolean'
}).help().locale('en').parse()

function costFunction(theta, n, mileage, price) {
    let squareSum = 0

    for (let i = 0; i < n; i++) {
        squareSum += Math.pow(price[i] - (theta[0] + theta[1] * mileage[i]), 2)
    }

    return squareSum / n
}

function computePartialDerivative(theta, n, mileage, price) {
    let derivative = [0, 0]
    let estimatedPrice
    let priceError

    for (let i = 0; i < n; i++) {
        estimatedPrice = theta[0] + theta[1] * mileage[i]
        priceError = estimatedPrice - price[i]
        derivative[0] += priceError
        derivative[1] += priceError * mileage[i]
    }

    derivative[0] /= n
    derivative[1] /= n

    return derivative
}

function plotTraining(dataset, theta, costHistory) {
    const mileageZeroPrice = -theta[0] / theta[1];

    nodeplotlib.plot([{
        name: 'cost function',
        x: costHistory.map((value, index) => index),
        y: costHistory,
        mode: 'scatter'
    }])

    nodeplotlib.plot([{
        name: 'training data',
        x: dataset.map(value => +value[0]),
        y: dataset.map(value => +value[1]),
        mode: 'markers'
    }, {
        name: 'linear regression',
        x: [0, mileageZeroPrice],
        y: [theta[0], theta[0] + theta[1] * mileageZeroPrice],
        type: 'scatter'
    }])
}

const iterations = 1000
const learningRate = 1

csv.readCsvFile('data.csv').then(data => {
    const dataset = data.filter(([mileage, price]) => !isNaN(mileage) && isFinite(mileage) && !isNaN(price) && isFinite(price))
    const mileage = dataset.map(value => +value[0])
    const price = dataset.map(value => +value[1])

    const mileageMin = Math.min(...mileage), mileageMax = Math.max(...mileage)
    const priceMin = Math.min(...price), priceMax = Math.max(...price)

    for (let i = 0; i < dataset.length; i++) {
        mileage[i] = (mileage[i] - mileageMin) / (mileageMax - mileageMin)
        price[i] = (price[i] - priceMin) / (priceMax - priceMin)
    }

    const theta = [0, 0]
    const costHistory = []

    for (let i = 0; i < iterations; i++) {
        const derivative = computePartialDerivative(theta, dataset.length, mileage, price)
        costHistory.push(costFunction(theta, dataset.length, mileage, price))

        theta[0] -= learningRate * derivative[0]
        theta[1] -= learningRate * derivative[1]
    }

    theta[1] = (theta[1] * (priceMax - priceMin)) / (mileageMax - mileageMin)
    theta[0] = (theta[0] * (priceMax - priceMin) + priceMin) - theta[1] * mileageMin

    if (argv.plot)
        plotTraining(dataset, theta, costHistory)

    return csv.writeCsvFile('train.csv', [theta])
}).then(() => {
    console.log('Training done, results have been saved in train.csv')

}).catch(err => {
    console.error(err)

    process.exit(1)
})
