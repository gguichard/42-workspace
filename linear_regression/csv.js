const fs = require('fs')

exports.readCsvFile = (path) => {
    return new Promise((resolve, reject) => {
        try {
            const buffer = fs.readFileSync(path)

            resolve(buffer.toString().split('\n').filter(String).map(data => data.split(',')))
        } catch (err) {
            reject(err)
        }
    })
}

exports.writeCsvFile = (path, data) => {
    return new Promise((resolve, reject) => {
        const content = data.map(current => current.join(',')).join('\n')

        fs.writeFile(path, content, err => {
            if (err)
                reject(err)
            else
                resolve(data)
        })
    })
}
