require('isomorphic-fetch');

const Server = require('./src/Server.bs.js');

Server.start(process.env.NATURE_TOKEN, 3000);
