Object.prototype.wrap = function(event) {
    let obj = this;
    return {
        handle: function(callback) {
            obj.addEventListener(event, callback);
        },
    };
};

Array.prototype.last = function() {
    return this[this.length - 1];
}