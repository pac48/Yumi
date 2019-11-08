
"use strict";

let getJ = require('./getJ.js')
let getC = require('./getC.js')
let getG = require('./getG.js')
let getM = require('./getM.js')
let getT = require('./getT.js')
let getTrajTorques = require('./getTrajTorques.js')
let getStaticTorques = require('./getStaticTorques.js')
let setTorques = require('./setTorques.js')

module.exports = {
  getJ: getJ,
  getC: getC,
  getG: getG,
  getM: getM,
  getT: getT,
  getTrajTorques: getTrajTorques,
  getStaticTorques: getStaticTorques,
  setTorques: setTorques,
};
