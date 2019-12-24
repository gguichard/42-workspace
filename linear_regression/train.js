const csv = require('./csv')
const nodeplotlib = require('nodeplotlib')
const yargs = require('yargs')

const argv = yargs.option('plot', {
    description: 'Plot linear regression on a chart',
    type: 'boolean'
}).help().locale('en').parse()

function costFunction(theta, n, mileage, price) {
    let square_sum = 0

    for (let i = 0; i < n; i++) {
        square_sum += Math.pow(price[i] - (theta[0] + theta[1] * mileage[i]), 2)
    }

    return square_sum / n
}

function computePartialDerivative(theta, n, mileage, price) {
    let derivative = [0, 0]
    let estimated_price
    let price_error

    for (let i = 0; i < n; i++) {
        estimated_price = theta[0] + theta[1] * mileage[i]
        price_error = estimated_price - price[i]
        derivative[0] += price_error
        derivative[1] += price_error * mileage[i]
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
        x: dataset.map(value => Number(value[0])),
        y: dataset.map(value => Number(value[1])),
        mode: 'markers'
    }, {
        name: 'linear regression',
        x: [0, mileageZeroPrice],
        y: [theta[0], theta[0] + theta[1] * mileageZeroPrice],
        type: 'scatter'
    }])
}

csv.readCsvFile('data.csv').then(async data => {
    const iterations = 1000
    const learningRate = 1

    const dataset = data.filter(value => !isNaN(value[0]) && !isNaN(value[1]))
    const mileage = dataset.map(value => Number(value[0]))
    const price = dataset.map(value => Number(value[1]))

    const mileageMin = Math.min(...mileage), mileageMax = Math.max(...mileage)
    const priceMin = Math.min(...price), priceMax = Math.max(...price)

    for (let i = 0; i < dataset.length; i++) {
        mileage[i] = (mileage[i] - mileageMin) / (mileageMax - mileageMin)
        price[i] = (price[i] - priceMin) / (priceMax - priceMin)
    }

    let theta = [0, 0]
    let costHistory = []
    let derivative

    for (let i = 0; i < iterations; i++) {
        derivative = computePartialDerivative(theta, dataset.length, mileage, price)
        costHistory.push(costFunction(theta, dataset.length, mileage, price))

        theta[0] -= learningRate * derivative[0]
        theta[1] -= learningRate * derivative[1]
    }

    theta[1] = (theta[1] * (priceMax - priceMin)) / (mileageMax - mileageMin)
    theta[0] = (theta[0] * (priceMax - priceMin) + priceMin) - theta[1] * mileageMin

    if (argv.plot)
        plotTraining(dataset, theta, costHistory)

    csv.writeCsvFile('train.csv', [theta]).then(() => {
        console.log('Training done, results have been saved in train.csv')

    }).catch(err => {
        console.error('Unable to save training result:', err)

        process.exit(1)
    })
}).catch(err => {
    console.error(err)

    process.exit(1)
})
