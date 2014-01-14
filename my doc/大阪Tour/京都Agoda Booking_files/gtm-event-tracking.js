var gtm = gtm || {};

gtm.CATS = {};
gtm.CATS.BOOKINGFORM = 'Booking Form';
gtm.CATS.HOTELPAGE = 'Hotel Page';

gtm.ACTS = {};
gtm.ACTS.BLUR = 'Blur';
gtm.ACTS.CLICK = 'Click';
gtm.ACTS.CHANGE = 'Change';
gtm.ACTS.HOVER = 'Hover';

gtm.EVT_CLICK = 0;
gtm.EVT_BLUR = 1;
gtm.EVT_CHANGE = 2;
gtm.EVT_HOVER = 3;

//Load on booking form
gtm.SIMPLE_EVENTS = [
    { className: '.f_firstname', eventType: gtm.EVT_BLUR, category: gtm.CATS.BOOKINGFORM, label: 'Field - First Name' },
    { className: '.f_lastname', eventType: gtm.EVT_BLUR, category: gtm.CATS.BOOKINGFORM, label: 'Field - Last Name' },
    { className: '.f_email', eventType: gtm.EVT_BLUR, category: gtm.CATS.BOOKINGFORM, label: 'Field - Email' },
    { className: '.f_emailconfirm', eventType: gtm.EVT_BLUR, category: gtm.CATS.BOOKINGFORM, label: 'Field - Email Confirm' },
    { className: '.f_phone', eventType: gtm.EVT_BLUR, category: gtm.CATS.BOOKINGFORM, label: 'Field - Phone' },
    { className: '.f_passport', eventType: gtm.EVT_CHANGE, category: gtm.CATS.BOOKINGFORM, label: 'Field - Passport' },
    { className: '.f_notme', eventType: gtm.EVT_CLICK, category: gtm.CATS.BOOKINGFORM, label: 'Field - Not Travelling' },
    { className: '.f_specialreqs', eventType: gtm.EVT_BLUR, category: gtm.CATS.BOOKINGFORM, label: 'Field - Special Requirements' },
    { className: '.f_nonsmoke', eventType: gtm.EVT_CLICK, category: gtm.CATS.BOOKINGFORM, label: 'Field - Non-Smoking' },
    { className: '.f_latecheckin', eventType: gtm.EVT_CLICK, category: gtm.CATS.BOOKINGFORM, label: 'Field - Late Check-in' },
    { className: '.f_earlycheckin', eventType: gtm.EVT_CLICK, category: gtm.CATS.BOOKINGFORM, label: 'Field - Early Check-in' },
    { className: '.f_highfloor', eventType: gtm.EVT_CLICK, category: gtm.CATS.BOOKINGFORM, label: 'Field - High Floor' },
    { className: '.f_largebed', eventType: gtm.EVT_CLICK, category: gtm.CATS.BOOKINGFORM, label: 'Field - Large Bed' },
    { className: '.f_twinbed', eventType: gtm.EVT_CLICK, category: gtm.CATS.BOOKINGFORM, label: 'Field - Twin Bed' },
    { className: '.f_airport', eventType: gtm.EVT_CLICK, category: gtm.CATS.BOOKINGFORM, label: 'Field - Airport' },
    { className: '.optout', eventType: gtm.EVT_CLICK, category: gtm.CATS.BOOKINGFORM, label: 'Opt Out' },
    { className: '.pnlmouseoverBookCond', eventType: gtm.EVT_HOVER, category: gtm.CATS.BOOKINGFORM, label: 'Booking Conditions - Hover' },
    { className: '.bookingcond', eventType: gtm.EVT_CLICK, category: gtm.CATS.BOOKINGFORM, label: 'Booking Conditions - Click' },
    { className: '.bookcond', eventType: gtm.EVT_HOVER, category: gtm.CATS.BOOKINGFORM, label: 'Viewed booking conditions' },
    { className: '.bestpriceimg', eventType: gtm.EVT_HOVER, category: gtm.CATS.BOOKINGFORM, label: 'Best price - image' },
    { className: '.bestprice', eventType: gtm.EVT_CLICK, category: gtm.CATS.BOOKINGFORM, label: 'Best price - link' },
    { className: '.taxfeehoverlnk', eventType: gtm.EVT_HOVER, category: gtm.CATS.BOOKINGFORM, label: 'Tax fee - hover link' },
    { className: '.taxfeehoverimg', eventType: gtm.EVT_HOVER, category: gtm.CATS.BOOKINGFORM, label: 'Tax fee - hover image' },
    { className: '.txtAdditionalNotes', eventType: gtm.EVT_BLUR, category: gtm.CATS.BOOKINGFORM, label: 'Field - Additional Notes' }

];


gtm.bindEvent = function(scope, category, label, eventType, opt_extraParams) {
	var extraParams = opt_extraParams || {};
    var action = '';
	//console.log(extraParams);

	switch(eventType) {
		case gtm.EVT_CLICK:
			scope.click(function () {
                _gaq.push(['t2._trackEvent', category, gtm.ACTS.CLICK, label]);
			});
			break;
		case gtm.EVT_BLUR:
			scope.blur(function () {
			    _gaq.push(['t2._trackEvent', category, gtm.ACTS.BLUR, label]);
			});
			break;
		case gtm.EVT_CHANGE:
			scope.change(function () {
			    _gaq.push(['t2._trackEvent', category, gtm.ACTS.CHANGE, label]);
			});
			break;
		case gtm.EVT_HOVER:
			scope.hover(function () {
			    _gaq.push(['t2._trackEvent', category, gtm.ACTS.HOVER, label]);
			}, function() {});
	}
};


gtm.bindGTMEventHandlers = function() {
	var nItems = gtm.SIMPLE_EVENTS.length;
	for (var i = 0; i < nItems; i++) {
		var item = gtm.SIMPLE_EVENTS[i];
		gtm.bindEvent($(item.className), item.category, item.label, item.eventType);
	}
};

//This function is specific for hotel pages
gtm.bindReviewFilters = function () {
	var reviewFilters = $('input[id^="ctl00_ctl00_MainContent_ContentMain_HotelReview1_"]:not([disabled])');
	reviewFilters.each(function () {
		var value = $(this).val();
		gtm.bindEvent($(this), gtm.CATS.HOTELPAGE, 'reviewfilter - '+value, gtm.EVT_CLICK);
	});
};

$(document).ready(function() {
	gtm.bindGTMEventHandlers();
	gtm.bindReviewFilters();
});