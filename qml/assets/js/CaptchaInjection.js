window.Android = {
     setCaptchaResponse: function(challenge, response) {
        var string = "qhumble" + "|" + challenge + "|" + response;
        console.info(string);
    }
}

