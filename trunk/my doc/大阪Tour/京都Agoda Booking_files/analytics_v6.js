var _gaq = _gaq || [];
var _ga = _ga || {};

//Ecommerce handling
_ga.processEcommerce = function () {
    if (_ga.hasOwnProperty('transactionId')) {
        _gaq.push(['t2._addTrans', _ga.transactionId, _ga.transactionAffiliation, _ga.transactionTotal, '0', '0', '', '', '']);

        var n_products = _ga.transactionProducts.length;
        for (var i = 0; i < n_products; i++) {
            var product = _ga.transactionProducts[i];

            var sku = product.sku;
            var name = product.name;
            var category = product.category;
            var price = product.price;
            var quantity = product.quantity;

            _gaq.push(['t2._addItem', _ga.transactionId, sku, name, category, price, quantity]);
        }

        _gaq.push(['t2._trackTrans']);
        return true;
    }

    return false;
};

//Dynamically setting CVs (eg via AJAX calls)
_ga.setCV = function (slot) {
    switch (slot) {
        case 25:
            if (_ga.hasOwnProperty('cv25')) {
                _gaq.push(['t2._setCustomVar', 25, 'p_roomsAvail', _ga.cv25, 3]);
                _gaq.push(['t2._trackEvent', 'cv_roomsAvail', 'triggerCV', _ga.cv25, 1, true]);
            }
            break;
        case 41:
            if (_ga.hasOwnProperty('cv41')) {
                _gaq.push(['t2._setCustomVar', 41, 's_loginStatus', _ga.cv41, 2]);
                _gaq.push(['t2._trackEvent', 'cv_loginStatus', 'triggerCV', _ga.cv41, 1, true]);
            }
            break;
        default:
            break;
    }
};

_ga.setVP = function () {
    if (_ga.hasOwnProperty('vp')) {
        //TODO: use _set page to set vpv on page object
        _gaq.push(['t2._trackPageview', _ga.vp]);
    } else if (_ga.hasOwnProperty('r404')) {
        _gaq.push(['t2._trackPageview', '/404/?url=' + document.location.pathname + document.location.search + '&ref=' + document.referrer]);
    } else {
        _gaq.push(['t2._trackPageview']);
    }
};

var domain = _gaq.domain || '.agoda.com';

var pluginUrl = '//www.google-analytics.com/plugins/ga/inpage_linkid.js';
_gaq.push(['t2._require', 'inpage_linkid', pluginUrl]);
_gaq.push(['t2._setAccount', 'UA-6446424-30']);
_gaq.push(['t2._setDomainName', domain]);
_gaq.push(['t2._setAllowLinker', true]);
_gaq.push(['t2._setAllowHash', false]);
_gaq.push(['t2._setSiteSpeedSampleRate', 15]);

//Set Campaign Parameters if non-direct visit and no utm_* parameters in URL
if ((_ga.hasOwnProperty('source') || _ga.hasOwnProperty('medium') || _ga.hasOwnProperty('campaign'))) {
    var defLabel = '(custom not set)';
    var s = _ga.source || defLabel;
    var m = _ga.medium || defLabel;
    var c = _ga.campaign || defLabel;

    var campaignStr = ['utm_source=', s, '&utm_medium=', m, '&utm_campaign=', c].join('');
    _gaq.push(['t2._set', 'campaignParams', campaignStr]);
}

//Custom Variables
if (_ga.hasOwnProperty('cv01')) {
    _gaq.push(['t2._setCustomVar', 1, 'p_country', _ga.cv01, 3]);
    _gaq.push(['t2._setCustomVar', 9, 's_country', _ga.cv01, 2]);
}
if (_ga.hasOwnProperty('cv02')) {
    _gaq.push(['t2._setCustomVar', 2, 'p_city', _ga.cv02, 3]);
    _gaq.push(['t2._setCustomVar', 10, 's_city', _ga.cv02, 2]);
}
if (_ga.hasOwnProperty('cv03')) {
    _gaq.push(['t2._setCustomVar', 3, 'p_hotel', _ga.cv03, 3]);
    _gaq.push(['t2._setCustomVar', 11, 's_hotel', _ga.cv03, 2]);
}
if (_ga.hasOwnProperty('cv04')) {
    _gaq.push(['t2._setCustomVar', 4, 'p_poi', _ga.cv04, 3]);
    _gaq.push(['t2._setCustomVar', 12, 's_poi', _ga.cv04, 2]);
}
if (_ga.hasOwnProperty('cv05')) {
    _gaq.push(['t2._setCustomVar', 5, 'p_region', _ga.cv05, 3]);
    _gaq.push(['t2._setCustomVar', 13, 's_region', _ga.cv05, 2]);
}
if (_ga.hasOwnProperty('cv06')) {
    _gaq.push(['t2._setCustomVar', 6, 'p_propertyType', _ga.cv06, 3]);
    _gaq.push(['t2._setCustomVar', 14, 's_propertyType', _ga.cv06, 2]);
}
if (_ga.hasOwnProperty('cv07')) {
    _gaq.push(['t2._setCustomVar', 7, 'p_stars', _ga.cv07, 3]);
    _gaq.push(['t2._setCustomVar', 15, 's_stars', _ga.cv07, 2]);
}
if (_ga.hasOwnProperty('cv08')) {
    _gaq.push(['t2._setCustomVar', 8, 'p_pageType', _ga.cv08, 3]);
}
if (_ga.hasOwnProperty('cv16')) {
    _gaq.push(['t2._setCustomVar', 16, 's_hotelGroup', _ga.cv16, 2]);
}
if (_ga.hasOwnProperty('cv17')) {
    _gaq.push(['t2._setCustomVar', 17, 's_roomType', _ga.cv17, 2]);
}
if (_ga.hasOwnProperty('cv22')) {
    _gaq.push(['t2._setCustomVar', 22, 's_cid', _ga.cv22, 2]);
}
if (_ga.hasOwnProperty('cv24')) {
    _gaq.push(['t2._setCustomVar', 24, 's_promoType', _ga.cv24, 2]);
}
if (_ga.hasOwnProperty('cv25')) {
    _gaq.push(['t2._setCustomVar', 25, 'p_roomsAvail', _ga.cv25, 3]);
}
if (_ga.hasOwnProperty('cv31')) {
    _gaq.push(['t2._setCustomVar', 31, 's_serverWeb', _ga.cv31, 2]);
}
if (_ga.hasOwnProperty('cv32')) {
    _gaq.push(['t2._setCustomVar', 32, 's_serverRes', _ga.cv32, 2]);
}
if (_ga.hasOwnProperty('cv36')) {
    _gaq.push(['t2._setCustomVar', 36, 's_checkoutStep', _ga.cv36, 2]);
}
if (_ga.hasOwnProperty('cv37')) {
    _gaq.push(['t2._setCustomVar', 37, 's_coupon', _ga.cv37, 2]);
}
if (_ga.hasOwnProperty('cv38')) {
    _gaq.push(['t2._setCustomVar', 38, 'v_nPastBookings', _ga.cv38, 1]);
}
if (_ga.hasOwnProperty('cv39')) {
    _gaq.push(['t2._setCustomVar', 39, 'v_nDaysLastPurchase', _ga.cv39, 1]);
}
if (_ga.hasOwnProperty('cv40')) {
    _gaq.push(['t2._setCustomVar', 40, 'v_lastSearch', _ga.cv40, 1]);
}
if (_ga.hasOwnProperty('cv41')) {
    _gaq.push(['t2._setCustomVar', 41, 's_loginStatus', _ga.cv41, 2]);
}
if (_ga.hasOwnProperty('cv46')) {
    _gaq.push(['t2._setCustomVar', 46, 'srt1', _ga.cv46, 2]);
}
if (_ga.hasOwnProperty('cv47')) {
    _gaq.push(['t2._setCustomVar', 47, 'srt2', _ga.cv47, 2]);
}
if (_ga.hasOwnProperty('cv48')) {
    _gaq.push(['t2._setCustomVar', 48, 'srt3', _ga.cv48, 2]);
}
if (_ga.hasOwnProperty('cv49')) {
    _gaq.push(['t2._setCustomVar', 49, 'srt4', _ga.cv49, 2]);
}
if (_ga.hasOwnProperty('cv50')) {
    _gaq.push(['t2._setCustomVar', 50, 'srt5', _ga.cv50, 2]);
}

_ga.setVP();

if (_ga.hasOwnProperty('transactionId')) {
    _ga.processEcommerce();
}

(function () {
    var ga = document.createElement('script');
    ga.type = 'text/javascript';
    ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://' : 'http://') + 'stats.g.doubleclick.net/dc.js';
    var s = document.getElementsByTagName('script')[0];
    s.parentNode.insertBefore(ga, s);
})();