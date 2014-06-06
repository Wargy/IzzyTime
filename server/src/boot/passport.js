var config = require("nconf");
var passport = require('passport');
var db=require('./../routes/database.js');
var AuthLocalStrategy = require('passport-local').Strategy;

passport.use('local', new AuthLocalStrategy(
    function (username, password, done) {
//чтение из бд
        var tabname=db.authorization(username,password);
if(tabname){
    return done(null, {
        tabname: tabname
    });
}else{
    return done(null, {
        tabname: "db"
    });
}

        return done(null, false, {
            message: 'Неверный логин или пароль'
        });
    }
));

passport.serializeUser(function (user, done) {
    done(null, JSON.stringify(user));
});


passport.deserializeUser(function (data, done) {
    try {
        done(null, JSON.parse(data));
    } catch (e) {
        done(err)
    }
});

module.exports = function (app) {
};