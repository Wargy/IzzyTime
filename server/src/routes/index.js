module.exports = function (app) {
    require("./home")(app);
    require("./auth")(app);
    require("./sync")(app);
  //  require("./../node_modules/database")(app);
};