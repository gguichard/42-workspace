const fs = require('fs')

exports.readCsvFile = function(path) {
    return new Promise((resolve, reject) => {
        try {
            const buffer = fs.readFileSync(path)

            resolve(buffer.toString().split('\n').filter(String).map(data => {
                return data.split(',')
            }))
        } catch (err) {
            reject('unable to open ' + path + ': ' + err)
        }
    })
}

exports.writeCsvFile = function(path, data) {
    return new Promise((resolve, reject) => {
        const content = data.map(current => current.reduce((previousValue, currentValue) => previousValue + currentValue + ',', '').replace(/,+$/g, '')).reduce((previousValue, currentValue) => previousValue + currentValue + '\n', '').replace(/\n+$/g, '')

        fs.writeFile(path, content, err => {
            if (err != null)
                reject('unable to write ' + path + ': ' + err)
            else
                resolve(data)
        })
    })
}
