const yargs = require('yargs')

const argv = yargs
    .command('train', 'Run training', {
        plot: {
            description: 'Plot linear regression on a chart',
            type: 'boolean'
        }
    })
    .command('predict', 'Predict the price of a vehicle')
    .demandCommand(1, 'You have to choose between `train` and `predict` commands')
    .help().locale('en').parse()

if (argv._.includes('train')) {
    require('./train')
} else if (argv._.includes('predict')) {
    require('./predict')
}
