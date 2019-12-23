const readline = require('readline')
const csv = require('./csv')

const inputInterface = readline.createInterface({
    input: process.stdin,
    output: process.stdout
})

async function estimatePrice(theta, mileage) {
    if (mileage < 0)
        console.error('Mileage should be positive')
    else
    {
        const price = theta[0] + theta[1] * mileage

        if (price < 0)
            console.error('Price is under $0')
        else
            console.log('Price for mileage ' + mileage + ' is $' + price)
    }
}

csv.readCsvFile('train.csv').then(async data => {
    const theta = [Number(data[0][0]), Number(data[0][1])]
    let answer

    while (true) {
        answer = await new Promise(resolve =>
            inputInterface.question('Type the mileage of your vehicle: ', resolve))

        if (isNaN(answer))
            console.error(answer + ' is not a number')
        else
            estimatePrice(theta, Number(answer))
    }
}).catch(err => {
    console.error(err)

    process.exit(1)
})
