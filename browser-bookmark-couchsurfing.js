javascript:(function(){
    function dateStr(plus_days) {
        var plus_days = (typeof plus_days !== 'undefined') ? plus_days : 0;
        var today = new Date(new Date().getTime() + plus_days * 24 * 60 * 60 * 1000);
        var strDate = 'Y-m-d'
            .replace('Y', today.getFullYear())
            .replace('m', (today.getMonth()+1).toLocaleString('en-US', {minimumIntegerDigits: 2, useGrouping:false}))
            .replace('d', today.getDate().toLocaleString('en-US', {minimumIntegerDigits: 2, useGrouping:false}));
        return strDate;
    }
    where = 'Moscow+Russian+Federation';
    location.href='https://www.couchsurfing.com/events/search?search_query=' + where + '&start_date=' + dateStr(1) + '&end_date=' + dateStr(1);
})();
