//Variable declartion
var FreeCanH = "";
var FreeCan = "";
var BookCondH = "";
var BookCond = "";
var TaxFeeH = "";                                           
var TaxFee = "";
var cmsAgeofChildH = "";
var cmsAgeofChild = "";
var cmsBookingConditions = "";
var cmsFreeCancellation = "";
var cmsFinalPrice = "";
var cmsPriceIncludesAll = "";
var cmsHotelTax = "";
var cmsBE3HotelTax = "";
var cmsEnterFlightHint = "";
var cmsExtraBed = "";
var cmsExtraBedCharge = "";
var cmsDomestic = "";
var beds = 4;
var isRequiredTitle = false;
var counter_flag = 0;
var timer;
var count = 10;
var isCancelled = true;
var isGA = false;
var isSuppressRewards = false;

var isguestall = false

if (typeof cctxt1 === 'undefined') {
    var cctxt1 = false;
}

if (typeof cctxt2 === 'undefined') {
    var cctxt2 = false;
}

if (typeof cctxt3 === 'undefined') {
    var cctxt3 = false;
}

if (typeof cctxt4 === 'undefined') {
    var cctxt4 = false;
}

if (typeof isagent === 'undefined') {
    var isagent = false;
}

if (typeof isAppliedCB === 'undefined') {
    var isAppliedCB = false;
}



if (typeof showcollected === 'undefined') {
    var showcollected = false;
}

// default guest no.
var guestNo = 1;
// The titleList.
var titleList = "";

if (typeof is1316 === 'undefined') {
    var is1316 = false;
}

if (typeof is1383 === 'undefined') {
    var is1383 = false;
}

if (typeof is1617 === 'undefined') {
    var is1617 = false;
}

if (typeof is1712 === 'undefined') {
    var is1712 = false;
}

if (typeof is1410 === 'undefined') {
    var is1410 = false;
}

if (typeof is1693 === 'undefined') {
    var is1693 = false;
}

if (typeof is1751 === 'undefined') {
    var is1751 = false;
}

if (typeof is1788 === 'undefined') {
    var is1788 = false;
}
if (typeof ab1788 === 'undefined') {
    var ab1788 = {};
}

if (typeof is1807 === 'undefined') {
    var is1807 = false;
}

if (typeof is1808 === 'undefined') {
    var is1808 = false;
}

if (typeof is1824 === 'undefined') {
    var is1824 = false;
}

if (typeof is1825 === 'undefined') {
    var is1825 = false;
}

// 1712

if (typeof flag === 'undefined') {
    var flag = false;
}

if (typeof paymentMethodPL === 'undefined') {
    var paymentMethodPL = "";
}

if (typeof errPL === 'undefined') {
    var errPL = "";
}

if (typeof chargedate === 'undefined') {
    var chargedate = "";
}

// end 1712

if (typeof cardvalidated === 'undefined') {
    var cardvalidated = false;
}

if (typeof expiryvalidated === 'undefined') {
    var expiryvalidated = false;
}

function GetPaymentModel() {
    var urlMethod = getUrlMethod("book.aspx", "GetPaymentModel");
    var jsonData = "{}";
    SendAjaxSync(urlMethod, jsonData, ReturnGetPaymentModel);
}

function ReturnGetPaymentModel(msg) {
    if (msg.d == "PayHotel") {
        isBookingCom = true;
    }
    else if (msg.d == "HotelBooking") {
        isBE3 = true;
    }
}

function ReturnSetGuestNationalityId(msg) {

    if (msg.d.length > 0) {

            $("#ddlCntctCountry").val("0");
        $("#ddlCountry_0").val("0");

        tb_show("BookingRestricted", "/b/popups/BookingRestricted.aspx?placeValuesBeforeTB_=savedValues&height=180&width=702&modal=true&cc=USD&p=" + p);
    }
}

function RewardMemberForgotPassword() {
    if ($("#txtForgot").val() != "") {
        var urlMethod = getUrlMethod("book.aspx", "RewardMemberForgotPassword");
        var jsonData = "{'username' : '" + $("#txtForgot").val() + "'}";
        SendAjax(urlMethod, jsonData, ReturnRewardMemberForgotPassword);
    }
    else {
        $("#divForgotError").html(rewardMemberProvideEmail);
    }
    return false;
}

function ReturnRewardMemberForgotPassword(msg) {
    $("#txtForgot").val("");
    if (msg.d.IsSuccess) {
        $("#divForgot").hide();
        $("#divDoneReset").show();
    }
    else {
        $("#divForgotError").html(msg.d.Message);
    }
}

function RewardMemberResetPassword() {
    if ($("#txtChangepwd").val() != "") {
        var urlMethod = getUrlMethod("book.aspx", "RewardMemberResetPassword");
        var jsonData = "{'username' : '" + $("#txtChangepwd").val() + "'}";
        SendAjax(urlMethod, jsonData, ReturnRewardMemberResetPassword);
    }
    else {
        $("#divChangeError").html(rewardMemberProvideEmail);
    }
    return false;
}

function ReturnRewardMemberResetPassword(msg) {
    $("#txtChangepwd").val("");
    if (msg.d.IsSuccess) {
        $("#divChangepwd").hide();
        $("#divDoneReset").show();
    }
    else {
        $("#divChangeError").html(msg.d.Message);
    }
}

function DoBook() {
    var urlMethod = getUrlMethod("book.aspx", "DoBook");
    var jsonData = "{}";
    SendAjax(urlMethod, jsonData, ReturnDoBooking);
}

function DoBookSync() {
    var urlMethod = getUrlMethod("book.aspx", "DoBook");
    var jsonData = "{}";
    SendAjaxSync(urlMethod, jsonData, ReturnDoBooking);
}

function ReturnDoBooking(msg) {
    disabledConfirm_exit = true;
    if (msg.d.StatusCode == -99) {
        var modalwidth = 500;
        if (languageId == 3) modalwidth = 600;
        tb_remove();
        setTimeout(function () { top.tb_show("RoomSoldOut", "/b/popups/RoomSoldOutPopup.aspx?height=auto&width=" + modalwidth + "&modal=true&p=" + p); }, 300);
    } else if (msg.d.StatusCode == 200 || msg.d.StatusCode == 0) {
        $(location).attr("href", msg.d.NextUrl);
    }
    else {
        // Pre-Auth Failed.
        $("#errCard").html("");
        $("#errCardNo").empty();

        tb_remove();
        if (msg.d.StatusCode == 419) {
            if (msg.d.NextUrl != "") {
                $(location).attr("href", msg.d.NextUrl);
            } else {
                //$("#errSum").append(msg.d.ErrorMessage);                   
                $("#errCard").append(msg.d.ErrorMessage);
                $("#errCard").show();
                if (is1788) {
                    $('html, body').animate({
                        scrollTop: $('#errCard').eq(0).focus().offset().top
                    }, 500);
                }
            } // 603, 604, 605, 606, 608, 609, 610, 611, 612, 613, 614, 615, 616
        } else if (msg.d.StatusCode == 603 || msg.d.StatusCode == 604 || msg.d.StatusCode == 605 || msg.d.StatusCode == 606 || msg.d.StatusCode == 608 || msg.d.StatusCode == 609 || msg.d.StatusCode == 610 || msg.d.StatusCode == 611 || msg.d.StatusCode == 612 || msg.d.StatusCode == 613 || msg.d.StatusCode == 614 || msg.d.StatusCode == 615 || msg.d.StatusCode == 616) {

//            if (msg.d.StatusCode == 609) {
//                jsonData = "{ 'chargeDate' : '" + chargedate + "','payment' : '" + $("#ddlPaymentMethod option:selected").text() + "' }";
//                SendAjax("/b/SendGenericMessage.aspx/SendDebitCardMessage?", jsonData);
//            } else {
//                jsonData = "{ 'chargeDate' : '" + chargedate + "','err' : '" + msg.d.ErrorMessage + "' }";
//                SendAjax("/b/SendGenericMessage.aspx/SendEBEErrorMessage?", jsonData);
//            }

            $("#errCardNo").append("<label class='error'>" + msg.d.ErrorMessage + "</label>");
            $("#errCardNo").show();
            if (is1788) {
                $('html, body').animate({
                    scrollTop: $('#errCardNo').eq(0).focus().offset().top
                }, 500);
            }
            tb_remove();
        } else if (msg.d.StatusCode == 302) {
            $(location).attr("href", msg.d.NextUrl);
        } else if (msg.d.StatusCode == 425) {
            $(location).attr("href", msg.d.NextUrl);
        } else if (msg.d.StatusCode == 473) {
            //$(location).attr("href", msg.d.NextUrl);
            Switch1StepBookingFail();
            $("#errSum").append(msg.d.ErrorMessage);
            GetBookingDetail();
        } else {
            $(location).attr("href", msg.d.NextUrl);
        }
    }
}

function LogoutReward() {
    var urlMethod = getUrlMethod("book.aspx", "LogoutReward");
    var jsonData = "{}";
    SendAjax(urlMethod, jsonData, ReturnLogoutReward);
    return false;
}

function ReturnLogoutReward(msg) {
    GetBookingDetail();

    $("#divRewardsLoginOn").hide();
    $("#divRedemption").hide();
    $("#divRewardsLogin").show();

    $("#txtCntFirstName").prop("disabled", false);
    $("#txtCntLastName").prop("disabled", false);
    $("#txtEmail").prop("disabled", false);
    $("#txtConfirmEmail").prop("disabled", false);
    $("#txtPhoneNo").prop("disabled", false);
    $("#txtEmail, #txtConfirmEmail").val("").removeClass("error valid").siblings().filter(".error-icon, .valid-icon").remove();
}

function RedeemRewardPoint() {
    var urlMethod = getUrlMethod("book.aspx", "RedeemRewardPoint");
    var jsonData = "{'strRewardPoint' : '" + $("#ddlRedeemPoints").val() + "'}";
    SendAjax(urlMethod, jsonData, ReturnRedeemRewardPoint);
}

function ReturnRedeemRewardPoint(msg) {
    if (msg.d.length > 0) {
        $("#pErrorRedeem").show();
        $("#pErrorRedeem").html(msg.d);
    }
    else {
        GetBookingDetail();
    }
}

function MemberLastNameCheck() {
    var clastname = "";
    var lastname = "";

    clastname = $("#txtCntLastName").val().toLowerCase();

    if ($("#chknotme").is(":checked") || isguestall) {
        lastname = $("#txtLastName_0").val().toLowerCase();
    } else {
        lastname = clastname;
    }

    //if ($("#txtCntctLastName_2").val().toLowerCase() != $("#txtLastName0").val().toLowerCase()) {
    if (clastname != lastname) {
        $("#ddlRedeemPoints").val('0;0;0;false');
        $("#ddlRedeemPoints").prop('disabled', true);
        $("#btnRedeemPoints").prop('disabled', true);
        $("#divRewardBalance").hide();
        $("#divRewardIncorrectGuestLastName").show();
        RedeemRewardPoint();
    }
    else {
        $("#ddlRedeemPoints").prop('disabled', false);
        $("#btnRedeemPoints").prop('disabled', false);
        $("#divRewardIncorrectGuestLastName").hide();
        $("#divRewardBalance").show();
    }
}

function LoginReward() {

    //Clear error...

    $("#errRewardUsername").empty();
    $("#errRewardPassword").empty();
    $("#pErrorRedeem").empty();
    $("#pErrorRedeem").hide();

    var isValid = true;

    //if (!($("#txtRewardUsername").valid()) && $("#txtRewardUsername").val() == "") {     
    if ($("#txtRewardUsername").val() == "") {
        $("#errRewardUsername")[0].innerHTML = rewardUserNameRequired;
        isValid = false;
    }

    //if (!($("#txtRewardPassword").valid()) && $("#txtRewardPassword").val() == "") {            
    if ($("#txtRewardPassword").val() == "") {
        $("#errRewardPassword")[0].innerHTML = rewardPasswordRequired;
        isValid = false;
    }

    if (isValid) {

        var urlMethod = getUrlMethod("book.aspx", "LoginReward");
        var jsonData = "{'username' : '" + $("#txtRewardUsername").val() + "', 'password' :'" + $("#txtRewardPassword").val() + "'}";

        SendAjax(urlMethod, jsonData, ReturnLoginReward);

        // Set cookie.
        var options = { path: '/', expires: 365 };
        if ($("#chkRewardsRemember").is(":checked")) {
            $.cookie('MemberUserName', $("#txtRewardUsername").val(), options);
        }
        else {
            $.cookie('MemberUserName', null, options);
        }
    }
    //    else {
    //        $("#txtRewardPassword").removeClass("valid");
    //        $("#txtRewardPassword").siblings().filter('div[class="valid-icon"]').remove();
    //    }

    return false;
}

function ReturnLoginReward(msg) {

    if (msg.d == null) {
        $("#divRewardsLoginOn").hide();
        $("#divRewardsError").show();
    }
    else {
        if (msg.d.IsLoggedIn) {
            $("#divRedemption").toggle();
            $("#divRewardsLoginOn").toggle();

            $("#ddlRedeemPoints").prop('disabled', false);
            $("#btnRedeemPoints").prop('disabled', false);

            // Fill the info.
            $("#divRewardWelcome").html(msg.d.WelcomeText);
            $("#divRewardBalance").html(msg.d.BalanceText);


            $("#txtCntFirstName").val(msg.d.FirstName).prop('disabled', true).valid();
            $("#txtCntLastName").val(msg.d.LastName).prop('disabled', true).valid();
            $("#txtEmail").val(msg.d.Email).prop('disabled', true).valid();
            $("#txtConfirmEmail").val(msg.d.Email).prop('disabled', true).valid();
            $("#txtPhoneNo").val(msg.d.Homephone).valid();

            if (isguestall) {
                if ($("#txtFirstName_0").val() == "") {
                    $("#txtFirstName_0").val(msg.d.FirstName);
                }

                if ($("#txtLastName_0").val() == "") {
                    $("#txtLastName_0").val(msg.d.LastName);
                }
            }

            // Reward Point.
            var listItems = "<option value='0;0;0;false'>" + rewardSelectOne + "</option>";
            for (var i = 0; i < msg.d.Points.length; i++) {
                listItems += "<option value='" + msg.d.Points[i].Point + ";" + msg.d.Points[i].Amount + ";" + msg.d.Points[i].Value + ";" + msg.d.HasCompleteBooking + "'>" + msg.d.Points[i].AmountText + "</option>";
            }
            $("#ddlRedeemPoints").html(listItems);
            $("#divRewardBalance").trigger('change');
            MemberLastNameCheck();

            $("#lnkRewardSite").attr("href", msg.d.RewardSiteUrl + "/index.html");
        }
        else {
            $("#errRewardPassword").empty();
            $("#errRewardPassword").append(rewardInvalidLogin);
        }
    }

    // Clear username & password.
    if (!$("#chkRewardsRemember").is(":checked")) {
        $("#txtRewardUsername").val("");
    }

    $("#txtRewardPassword").val("");
}

function Initialize() {

    $("#bkg_divDiscount").hide();
    //Get Cookie
    var MemberUserName = $.cookie('MemberUserName');
    if (MemberUserName != '') {
        $("#txtRewardUsername").val(MemberUserName);
        $("#chkRewardsRemember").prop("checked", true);
    }

    //[workaround|taskid:6015] make the booking details corrensponding to the login status everytime the page get refreshed.
    LogoutReward();
}

function DinersCardNumberSetFocus(index) {
    var txtLen = [4, 5, 5];
    // if (!(isiPad() || isiPhone())) {
    if ($('#txtDiners_' + index).val().length == txtLen[index]) {
        if ($('#txtDiners_0').val().length == 4) {
            if ($('#txtDiners_1').val().length == 5) {
                if ($('#txtDiners_2').val().length == 5) {
                    if (!(isiPad() || isiPhone()))
                        $('#txtHolderName').focus().val($('#txtHolderName').val());
                    // The credit number input has been completed. then check the promotion.
                    GetPromotions();
                }
                else {
                    if (!(isiPad() || isiPhone()))
                        $('#txtDiners_2').focus().val($('#txtDiners_2').val());
                }
            }
            else {
                if (!(isiPad() || isiPhone()))
                    $('#txtDiners_1').focus().val($('#txtDiners_1').val());
            }
        }
        else {
            if (!(isiPad() || isiPhone()))
                $('#txtDiners_0').focus().val($('#txtDiners_0').val());
        }
    }
    else {
        if (!(isiPad() || isiPhone()))
            $('#txtDiners_').focus().val($('#txtDiners_').val());
    }
    //}
}

function AmexCardNumberSetFocus(index) {
    var txtLen = [4, 6, 5];
    if ($('#txtAmex_' + index).val().length == txtLen[index]) {
        if ($('#txtAmex_0').val().length == 4) {
            if ($('#txtAmex_1').val().length == 6) {
                if ($('#txtAmex_2').val().length == 5) {
                    if (!(isiPad() || isiPhone()))
                        $('#txtHolderName').focus().val($('#txtHolderName').val());
                    // The credit number input has been completed. then check the promotion.
                    GetPromotions();
                }
                else {
                    if (!(isiPad() || isiPhone()))
                        $('#txtAmex_2').focus().val($('#txtAmex_2').val());
                }
            }
            else {
                if (!(isiPad() || isiPhone()))
                    $('#txtAmex_1').focus().val($('#txtAmex_1').val());
            }
        }
        else {
            if (!(isiPad() || isiPhone()))
                $('#txtAmex_0').focus().val($('#txtAmex_0').val());
        }
    }
    else {
        if (!(isiPad() || isiPhone()))
            $('#txtAmex_').focus().val($('#txtAmex_').val());
    }
}

function CardNumberSetFocus(index) {
    if ($('#txtCard_' + index).val().length == 4) {
        var nextIndex = -1;
        for (var i = index + 1; i < 4; i++) {
            if ($('#txtCard_' + i).val().length < 4) {
                nextIndex = i;
                break;
            }
        }
        if (nextIndex == -1) {
            for (var i = 0; i < 4; i++) {
                if ($('#txtCard_' + i).val().length < 4) {
                    nextIndex = i;
                    break;
                }
            }
            if (nextIndex == -1) {
                if (!(isiPad() || isiPhone()))
                    $('#txtHolderName').focus().val($('#txtHolderName').val());
                // The credit number input has been completed. then check the promotion.
                GetPromotions();
            }
            else {
                if (!(isiPad() || isiPhone()))
                    $('#txtCard_' + nextIndex).focus().val($('#txtCard_' + nextIndex).val());
            }
        }
        else {
            if (!(isiPad() || isiPhone()))
                $('#txtCard_' + nextIndex).focus().val($('#txtCard_' + nextIndex).val());
        }
    }
}

function ReturnRequestExtraBed(msg) {
    if (msg.d.IsSuccess) {
        GetBookingDetail();
    }

    $("#divloading").hide();
    if ($('#btnContinue').prop('disabled')) {
        $('#btnContinue').prop('disabled', false).addClass('blue_roundbtn').removeClass('blue_roundbtn_disabled');
    }
}

function RequestExtraBedOnOccFreeRoom(roomId, obj) {

    $("#btnContinue").prop("disabled", true).addClass('blue_roundbtn_disabled').removeClass('blue_roundbtn');
    $("#divloading").show();

    if (timer) {
        clearInterval(timer);
        timer = null;
    }
    count = 10;

    timer = setInterval(function () {
        count--;

        if (count === 0) {
            clearInterval(timer);
            timer = null;

            if ($('#btnContinue').prop('disabled')) {
                $('#btnContinue').prop('disabled', false).addClass('blue_roundbtn').removeClass('blue_roundbtn_disabled');
            }

            $("#divloading").hide();
        }
    }, 1000);

    var urlMethod = getUrlMethod("book.aspx", "RequestExtraBedOnOccFreeRoom");
    var jsonData = "{roomId : '" + roomId + "', useExtrabed : " + $(obj).is(":checked") + "}";

    SendAjax(urlMethod, jsonData, ReturnRequestExtraBedOnOccFreeRoom);
}

function ReturnRequestExtraBedOnOccFreeRoom(msg) {
    if (msg.d.IsSuccess) {
        GetBookingDetail();
    }

    // isCancelled = true;
    $("#divloading").hide();
    if ($('#btnContinue').prop('disabled')) {
        $('#btnContinue').prop('disabled', false).addClass('blue_roundbtn').removeClass('blue_roundbtn_disabled');
    }
}

function ReturnSetChildAge(msg) {
    if (msg.d.IsSuccess) {
        // Clear the message
        $("[id^=divAgeMessage]").html('').hide();
        $("[id^=divExtraBedOffer]").hide();
        for (var j = 0; j < msg.d.Index.length; j++) {
            $("#divAgeMessage" + (msg.d.Index[j] - 1)).html(msg.d.Message).show();
        }

        for (var k = 0; k < msg.d.OfferExtraBedIndex.length; k++) {
            $("#divExtraBedOffer" + (msg.d.OfferExtraBedIndex[k] - 1)).show();
        }
        GetBookingDetail();
    }

    // isCancelled = true;
    $("#divloading").hide();
    if ($('#btnContinue').prop('disabled')) {
        $('#btnContinue').prop('disabled', false).addClass('blue_roundbtn').removeClass('blue_roundbtn_disabled');
    }
}

escape = function (str) {
    return str
        .replace(/[\\]/g, '\\\\')
        .replace(/[\"]/g, '\\\"')
        .replace(/[\/]/g, '\\/')
        .replace(/[\b]/g, '\\b')
        .replace(/[\f]/g, '\\f')
        .replace(/[\n]/g, '\\n')
        .replace(/[\r]/g, '\\r');

};

function SetFirstDisplayScreen() {

    BindExpiryYear();
    BindExpiryMonth();

    BindEventToElements();
    //GetPaymentModel();
    //beds = 4;               //sets the extra beds here
    AssignFormElements();
    AssignHovers();           //assign static links hover
}

function BindEventToElements() {

    // Events.
    var stuff = [];
    var ageElems;

    $('#chknotme').on('click', function () {
        if ($(this).prop("checked")) {
            stuff = [];
            ageElems = $("#guestHolder select[id^=ddlAge]:visible");
            jQuery.each($(ageElems), function (i, elem) {
                stuff.push($(elem).val());
            });

            $('#divguestName').show();
            $("#guestHolder").hide();
            var str = $("#guestHolder").html();
            $("#guestHolder").html("");
            $("#guestHolder_2").html(str);

            if (stuff.length > 0) {
                ageElems = $("#guestHolder_2 select[id^=ddlAge]:visible");
                jQuery.each($(ageElems), function (i, elem) {
                    $(elem).val(stuff[i]);
                });
            }

        } else {

            ageElems = $("#guestHolder_2 select[id^=ddlAge]:visible");
            stuff = [];
            jQuery.each($(ageElems), function (i, elem) {
                stuff.push($(elem).val());
            });

            $('#divguestName').hide();

            var str = $("#guestHolder_2").html();
            $("#guestHolder_2").html("");
            $("#guestHolder").html(str);
            $("#guestHolder").show();

            if (stuff.length > 0) {
                ageElems = $("#guestHolder select[id^=ddlAge]:visible");
                jQuery.each($(ageElems), function (i, elem) {
                    $(elem).val(stuff[i]);
                });
            }
            //$("#ddlRedeemPoints").prop('disabled', false);
        }

        MemberLastNameCheck();
        AssignHoverDyn("AgeofChild");
    });

    $('#btnSubmit').click(function () {

        Submitbooking();
        return false;
    });

    $('#btnContinue').click(function () {
        if (ValidateFormStep1())
            SubmitFirstStepClicked();

        if ($('.error:visible').length) {
            $('html, body').animate({
                scrollTop: $('.error:visible').eq(0).focus().offset().top - 24
            }, 500);
            $('.error:visible').eq(0).focus();
        }

        if (is1712)
            $("#divBNPLOption").show();

        return false;
    });

    $('#btnBack').click(function () {

        if (step != 1) {
            $("#divHeadTitle")[0].innerHTML = cmsBookingDetail;
            step = 1;
            $('#divstep1').show();
            $('#divstep2').hide();

            $('#btnBack, #btnBack1788').hide();
            $('#btnContinue, #btnContinue1788').show();
            $('#btnSubmit, #btnSubmit1788').hide();

            $('#pnlTotalPrice').hide();

            if (is1693) {
                $('#divExcludedTaxDetail').hide();
                $('#trFinalPrice').hide();
            }

            if (isAppliedCB || (ispartAppliedCB && is1678))
                $('#notincluded').show();

            SetupBlueButtons();

            if (is1712) {
                ab1712.SetupStep1();
            }

            if (is1788) {
                $('html, body').animate({
                    scrollTop: $('#logowrapper').eq(0).focus().offset().top
                }, 500);
                if (ab1788.hasRewards) {
                    $('#bkg_divRewards').show();
                }
        }
        }

        return false;
    });

    $('#txtCard_0').keypress(function (e) {
        CheckNumeric2(e);
    });

    $('#txtCard_0').keyup(function (e) {
        CardNumberSetFocus(0);
    });

    $('#txtCard_0').bind("contextmenu", function (event) { return false; });

    $('#txtCard_1').keypress(function (e) {
        CheckNumeric2(e);
    });

    $('#txtCard_1').keyup(function (e) {
        CardNumberSetFocus(1);
    });

    $('#txtCard_1').bind("contextmenu", function (event) { return false; });

    $('#txtCard_2').keypress(function (e) {
        CheckNumeric2(e);
    });

    $('#txtCard_2').keyup(function (e) {
        CardNumberSetFocus(2);
    });

    $('#txtCard_2').bind("contextmenu", function (event) { return false; });

    $('#txtCard_3').keypress(function (e) {
        CheckNumeric2(e);
    });

    $('#txtCard_3').keyup(function (e) {
        CardNumberSetFocus(3);
    });

    $('#txtCard_3').bind("contextmenu", function (event) { return false; });

    $('#txtAmex_0').keypress(function (e) { CheckNumeric2(e); });
    $('#txtAmex_1').keypress(function (e) { CheckNumeric2(e); });
    $('#txtAmex_2').keypress(function (e) { CheckNumeric2(e); });

    $('#txtAmex_0').keyup(function (e) { AmexCardNumberSetFocus(0); });
    $('#txtAmex_1').keyup(function (e) { AmexCardNumberSetFocus(1); });
    $('#txtAmex_2').keyup(function (e) { AmexCardNumberSetFocus(2); });

    $('#txtAmex_0').bind("contextmenu", function (event) { return false; });
    $('#txtAmex_1').bind("contextmenu", function (event) { return false; });
    $('#txtAmex_2').bind("contextmenu", function (event) { return false; });

    $('#txtDiners_0').keypress(function (e) { CheckNumeric2(e); });
    $('#txtDiners_1').keypress(function (e) { CheckNumeric2(e); });
    $('#txtDiners_2').keypress(function (e) { CheckNumeric2(e); });

    $('#txtDiners_0').keyup(function (e) { DinersCardNumberSetFocus(0); });
    $('#txtDiners_1').keyup(function (e) { DinersCardNumberSetFocus(1); });
    $('#txtDiners_2').keyup(function (e) { DinersCardNumberSetFocus(2); });

    $('#txtDiners_0').bind("contextmenu", function (event) { return false; });
    $('#txtDiners_1').bind("contextmenu", function (event) { return false; });
    $('#txtDiners_2').bind("contextmenu", function (event) { return false; });

    $('#txtCvc').keypress(function (e) {
        CheckNumeric2(e);
    });

    $('#txtCvc').bind("contextmenu", function (event) { return false; });
    $("#txtEmail").blur(GetPromotions);

    $("#txtLastName_0").blur(MemberLastNameCheck);

    $("#txtCntFirstName").blur(function () {

        if (($("#txtCntFirstName").val().length) > 0 && ($.trim($("#txtFirstName_0").val()) == "") && isguestall) {
            var reg_allow = new RegExp("^[a-zA-Z- ]+$", "g");
            var reg_delete = new RegExp("[^a-zA-Z- ]+", "g");

            if (($("#txtCntFirstName").val()).match(reg_allow) != null) {
                var custname = ($("#txtCntFirstName").val()).replace(reg_delete, "");
                $("#txtFirstName_0").val(custname);
            }
        }

        if ($.trim("#txtCntFirstName") != "" && $.trim($("#txtCntLastName").val()) != "") {
            $("#errContact_1").empty();
        }
    });

    $("#txtCntLastName").blur(function () {

        if (($("#txtCntLastName").val().length) > 0 && ($.trim($("#txtLastName_0").val()) == "") && isguestall) {

            var reg_allow = new RegExp("^[a-zA-Z- ]+$", "g");
            var reg_delete = new RegExp("[^a-zA-Z- ]+", "g");

            if (($("#txtCntLastName").val()).match(reg_allow) != null) {
                var custname = ($("#txtCntLastName").val()).replace(reg_delete, "");
                $("#txtLastName_0").val(custname);
            }
        }

        if ($.trim($("#txtCntFirstName").val()) != "" && $.trim($("#txtCntLastName").val()) != "") {
            $("#errContact_1").empty();
        }
    });

    $("#txtAddress").blur(function () {
        if ($.trim($("#txtAddress").val()) != "") {
            $("#txtAddress").css("border-color", "#8D9AA3");
            $("#errContact_3").empty();
        }
    });

    $("#txtCity, #txtPostal").blur(function () {
        if ($.trim($(this).val()) != "") {
            $(this).css("border-color", "#8D9AA3");
        }

        if ($.trim($("#txtCity").val()) != "" && $.trim($("#txtPostal").val()) != "") {
            $("#errContact_4").empty();
        }

    });

    $("#box_left").keypress(function (e) {
        if ((e.which && e.which == 13) || (e.keyCode && e.keyCode == 13)) {
            $(this).blur();
            $('#btnContinue, #btnSubmit').filter(':visible').eq(0).click();
            return false;
        }
    });

    if (navigator.userAgent.indexOf('Chrome') >= 0) {
        $('#txtCard_0, #txtAmex_0, #txtDiners_0').keypress(function (e) {
            if (
                (e.which && e.which == 9) || (e.keyCode && e.keyCode == 9) ||
                (e.which && e.which == 13) || (e.keyCode && e.keyCode == 13)) {
                return false;
            }
        });
    }

    if (navigator.userAgent.indexOf('Firefox') >= 0) {
        $('#ddlPaymentMethod').keypress(function (e) {
            if ((e.which && e.which == 13) || (e.keyCode && e.keyCode == 13)) {
                return false;
            }
        });
    }

    $("#ddlCntctCountry").focusout(function (e) {
        if ($("#ddlCntctCountry").val() > 0) {
            $("#errContact_5").empty();
            $("#ddlCntctCountry").css("border-color", "#8D9AA3");

            if ($("#ddlCountry_0").val() <= 0 && isguestall) {
                $("#ddlCountry_0").val($("#ddlCntctCountry").val());
                $("#ddlCountry_0").change();
            }

            var urlMethod = getUrlMethod("book.aspx", "SetGuestNationalityId");
            var jsonData = "{'nationalityId' : " + $("#ddlCntctCountry").val() + "}";
            SendAjax(urlMethod, jsonData, ReturnSetGuestNationalityId);
        }
    });

    $("#txtEmail").blur(function () {
        if (($(this).val().length) > 0 && $(this).val().match(/^([A-Za-z0-9_\-\.])+\@([A-Za-z0-9_\-\.])+\.([A-Za-z]{2,4})$/)) {
            $("#errContact_2").empty();
            $("#txtEmail").css("border-color", "#8D9AA3");
        }
    });

    $("#txtPhoneNo").blur(function () {
        if (($(this).val().length) > 0) {
            $("#errContact_6").empty();
            $("#txtPhoneNo").css("border-color", "#8D9AA3");
        }
    });

    $("#ddlCountry_0").change(function (e) {
        if ($("#ddlCountry_0").val() > 0) {

            var urlMethod = getUrlMethod("book.aspx", "SetGuestNationalityId");
            var jsonData = "{'nationalityId' : " + $("#ddlCountry_0").val() + "}";
            SendAjax(urlMethod, jsonData, ReturnSetGuestNationalityId);
        }
    });

    var childEles = $("#guestHolder_2 select[id^=ddlAge]:visible");
    childEles.change(function () {
        var iscompleted = false;

        jQuery.each($(childEles), function (i, elem) {
            if ($(this).val() != "0" && $(this).val() != "-1" && $(this).val() != "") {
                $(this).css("border-color", "#8D9AA3");
                iscompleted = true;
            } else {
                iscompleted = false;
                return (iscompleted);
            }
        });

        if (iscompleted)
            $('#errGuest_3').empty();
    });

    // var guestElems = $("#divguestName input:text[id^=txtFirstName],[id^=txtLastName]");
    var guestElems = $("#divguestName input[type=text]:visible, #divguestName select[id^=ddlCountry]");
    guestElems.change(function () {
        var iscompleted = false;
        jQuery.each($(guestElems), function (i, elem) {
            if (elem.tagName == "SELECT") {
                if ($(this).val() != "0" && $(this).val() != "-1" && $(this).val() != "") {
                    // $(this).css("border-color", "#8D9AA3");
                    iscompleted = true;
                } else {
                    iscompleted = false;
                    return (iscompleted);
                }
            } else if (elem.tagName == "INPUT") {
                if ($.trim($(this).val()) != "") {
                    iscompleted = true;
                }
                else {
                    iscompleted = false;
                    return (iscompleted);
                }
            }
        });
        if (iscompleted)
            $("#errGuest_2").empty();

    }).blur(function () {
        jQuery.each($(guestElems), function (i, elem) {
            if (elem.tagName == "SELECT") {
                if ($(this).val() != "0" && $(this).val() != "-1" && $(this).val() != "") {
                    $(this).css("border-color", "#8D9AA3");
                }
            } else if (elem.tagName == "INPUT") {
                if ($.trim($(this).val()) != "") {
                    $(this).css("border-color", "#8D9AA3");
                }
            }
        });
    });

    var paymentElems = $('#divPayment select:visible,#divPayment input[type=text]:visible,#bkg_divCountryIssueBank select');
    paymentElems.change(function () {
        var iscompleted = false;
        jQuery.each($(paymentElems), function (i, elem) {

            if (elem.tagName == "SELECT") {
                if ($(this).val() != "0" && $(this).val() != "-1" && $(this).val() != "") {
                    // $(this).css("border-color", "#8D9AA3");
                    iscompleted = true;
                } else {
                    iscompleted = false;
                    return (iscompleted);
                }
            }
            else if (elem.tagName == "INPUT") {
                if ($.trim($(this).val()) != "") {
                    //$(this).css("border-color", "#8D9AA3");
                    iscompleted = true;
                }
                else {
                    iscompleted = false;
                    return (iscompleted);
                }
            }
        });

        if (iscompleted)
            $("#errPayment_4").empty();

    }).blur(function () {
        jQuery.each($(paymentElems), function (i, elem) {
            if (elem.tagName == "SELECT") {
                if ($(this).val() != "0" && $(this).val() != "-1" && $(this).val() != "") {
                    $(this).css("border-color", "#8D9AA3");
                }

            } else if (elem.tagName == "INPUT") {
                if ($.trim($(this).val()) != "") {
                    if (elem.id == "txtCvc") {
                        if ($("#ddlPaymentMethod").val() == 4) {
                            if ($(this).val().length == 4)
                                $("#errPayment_3").empty();
                        } else {
                            if ($(this).val().length == 3)
                                $("#errPayment_3").empty();
                        }
                    }

                    $(this).css("border-color", "#8D9AA3");

                }
            }
        });
    });

    $("input:text[id^=txtCard], [id^=txtAmex], [id^=txtDiners]").keydown(CardNumberKeyPress);
    $("input:text:not([id^=txtCard]):not([id^=txtAmex]):not([id^=txtDiners]):not([id^=txtFirstName]):not([id^=txtLastName]):not('#txtCntFirstName'):not('#txtCntLastName'):not('#txtFlightNo'):not('#txtDeFlightNo'):not('#txtPhoneNo') ,textarea").keyup(ValidateGeneralInput);
    //$("input:#txtHolderName").keyup(ValidateNameDotInput);
    $(document).on('keyup', "input:text[id^=txtFirstName],[id^=txtLastName],#txtCntFirstName,#txtCntLastName,#txtHolderName", function (e) { ValidateNameInput(e); });


    $("#btnRedeemPoints").click(function () {
        RedeemRewardPoint();
        return false;
    });

    // Rewards
    $("#btnLoginOn").click(LoginReward);
    $("#btnForgot").click(RewardMemberForgotPassword);
    $("#btnChangepwd").click(RewardMemberResetPassword);
    $("#btnLogout").click(LogoutReward);

}

function AssignFormElements() {

    //Extra bed/Occupancy Free - toggle plus minus
    $("#bkg_llblExtrabedOccFree").click(function () {
        $("#bkg_pnlExtrabedOccFree").toggle();
        if ($(this).hasClass("plus")) {
            $(this).addClass("minus").removeClass("plus");
        }
        else {
            $(this).addClass("plus").removeClass("minus");
        }
    });

    //Extra bed/Special Request - toggle plus minus
    $("#bkg_lLblSpecialRequest").click(function () {
        $("#bkg_pnlSpecialRequest").toggle();
        if ($(this).hasClass("plus")) {
            $(this).addClass("minus").removeClass("plus");
        }
        else {
            $(this).addClass("plus").removeClass("minus");
        }
    });

    var txtAirTrans = $('#bkg_txtFightNoArrivalTime')
    var chkAirTrans = $('#chkAirportTrans');
    var searchLabel = unescapeString(cmsEnterFlightHint);
    if (chkAirTrans.prop("checked")) {
        txtAirTrans.prop("disabled", false).removeClass('disabled');
    }
    else txtAirTrans.prop("disabled", true).addClass('disabled').addClass('placeholder').val(searchLabel);
    //placeholder for textarea
    chkAirTrans.bind("change load", function () {
        if ($(this).prop("checked")) {
            txtAirTrans.prop("disabled", false).removeClass('disabled');
        }
        else txtAirTrans.prop("disabled", true).addClass('disabled');
    });
    txtAirTrans.focus(function () {
        if (this.value == searchLabel && !(txtAirTrans.prop("disabled"))) {
            $(this).removeClass('placeholder').val('');
        };
    }).blur(function () {
        if (this.value == '' && !(txtAirTrans.prop("disabled"))) {
            $(this).addClass('placeholder').val(searchLabel);
        };
    });

    //set credit card input hidden
    $("#bkg_divCountryIssueBank").hide();
    $("#bkg_divWhichBank").hide();

    //Credit card ddl
    SetTriggerPayment();

    //set Panels, divs starting show/hide state
    if (isBookingCom || isBE3) {
        if (isBE3) {
            $("#header, #bkdc_credithint .blacktext").hide()
            $("#box_bkdcnote .notetext").removeClass("wauto");
            $("#box_bkdcnote .price, #be3txt").show();
            $(".div_bestprice, #footerLink, #lblCopyRight, #lblPriceline, #lnkCardInfo").hide();

            $("#divChkLatOffer").hide();
            $("#bkdc_credithint").hide();
        }
        else if (isBookingCom) {
            $("#pnlCntctBkdc, #bkdctxt, #lnkCardInfo,.div_bestprice").show();
        }


        $("#box_bkdcnote").show();
        $("#bkdc_credithint").show();

    } else {
        // Check if it has to suppress the rewards login.        
        $("#box_bkdcnote, #pnlCntctBkdc").hide();
        $(".div_bestprice, #lblCopyRight, #lblPriceline").show();
        $("#bkdc_credithint").hide();
    }

    $("#divRewardsLoginOn").hide();
    $("#divRedemption").hide();
    $("#divForgot").hide();
    $("#divChangepwd").hide();

    //    $("#lnkBackToStep1, #navBtn1, #navTxt1").click(function () {
    //        if (step != 1) {
    //            SwitchTo1stStep();
    //        }
    //        //ValidateFormFilled();
    //        return false;
    //    });

    $("#btnLogin").click(function () {
        $("#divRewardsLogin").hide();
        $("#divRewardsLoginOn").show();
        return false;
    });
    $("#btnLoginClose").click(function () {
        $("#divRewardsLogin").show();
        $("#divRewardsLoginOn").hide();
        return false;
    });
    $("#btnErrorClose").click(function () {
        $("#divRewardsLogin").show();
        $("#divRewardsError").hide();
        return false;
    });
    $("#lnkForgot").click(function () {
        $("#divForgot").show();
        $("#divRewardsLoginOn").hide();
        $("#divForgotError").html("");

        if (is1788) {
            $('html, body').animate({
                scrollTop: $('#divForgot').eq(0).focus().offset().top
            }, 500);
        }

        BookingForm.Utils.technoMessage(3130, 0, 'Forgot Password A Version');
        return false;
    });
    $("#btnForgotClose").click(function () {
        $("#divForgot").hide();
        $("#divRewardsLoginOn").show();
        return false;
    });
    $("#lnkChangepwd").click(function () {
        $("#divChangepwd").show();
        $("#divRewardsLoginOn").hide();
        $("#divChangeError").html("");
        return false;
    });
    $("#btnChangepwdClose").click(function () {
        $("#divChangepwd").hide();
        $("#divRewardsLoginOn").show();
        return false;
    });
    $("#btnDoneReset").click(function () {
        $("#divDoneReset").hide();
        $("#divRewardsLoginOn").show();
        return false;
    });
}

function ClearBlueBar() {
    var bottombar = $(".box_leftborder .rbottom b, div[id^=divContBtn]");
    bottombar.removeClass("filled");
}

//Assign hover popups after json load completed
function AssignHovers() {
    AssignHoverDyn("BestPrice");
    AssignHoverDyn("CVC");
    AssignHoverDyn("CountryIssue");
    AssignHoverDyn("WhichBank");
    AssignHoverDyn("NeverShare");
}

// Returns from checking the currency.
function ReturnCheckCurrency(msg) {

    if (!msg.d.IsRedirectCard) {
        
        if (is1751 && $('#ddlIssueBankCountry').is(':visible')) {
            var ddl = $('#ddlChargeMeIn');
            if (ddl.is(':visible') && ddl[0].selectedIndex >= 0) {
                ab1751.SetCurrencyCode($('#ddlChargeMeIn option').eq(0).val(), ddl[0].selectedIndex);
            } else {
                DoBook();
            }            
        } else {
            if (msg.d.IsCardCurrencyMismatch) {
                // Remove Please wait..
                tb_remove();
                var height = "190";
                if (isiPadPortrait())
                    height = "600";
                setTimeout(function () { top.tb_show("ConfirmCurrency", "/b/ConfirmCurrency.aspx?placeValuesBeforeTB_=savedValues&height=" + height + "&width=340&modal=true&p=" + p); }, 300);
            }
            else {
                DoBook();
            }
        }
    }
    else {
        // Redirect card.
        tb_remove();
        if (msg.d.IsServiceDown || msg.d.Action == 2 || msg.d.Action == 5 || msg.d.Action == 1) {
            SetPaymentGatewayFail(msg.d.Message);
        }
        else {
            disabledConfirm_exit = true;
            setTimeout(function () { top.tb_show("ConfirmRedirect", "/b/popups/RedirectPayment.aspx?placeValuesBeforeTB_=savedValues&modal=true&p=" + p); }, 300);
        }
    }
}

function ClearNav() {
    //$('[id^="navTxt"]').removeClass("active");
    //$('[id^="navBtn"]').removeClass("bulletbgover bulletbg").addClass("bulletbg");
    $('#navTxt1,#navTxt2,#navTxt3').removeClass("active able");
    $('#navBtn1,#navBtn2,#navBtn3').removeClass("bulletbgover bulletbg able").addClass("bulletbg");
    //$("#navBtn1, #navTxt1").die("click");
}

function InitNav() {
    ClearNav();
    $("#navBtn1").removeClass("bulletbg bulletbgpass").addClass("bulletbgover");
    $("#navTxt1").addClass("active");

}

function UpdateNav2ndStep() {
    $("#navBtn1").removeClass("bulletbgover").addClass("bulletbgpass able");
    $("#navBtn2").removeClass("bulletbg").addClass("bulletbgover");
    $("#navTxt1").removeClass("active").addClass("able");
    $("#navTxt2").addClass("active");
}

function UpdateNavFinalStep() {
    $("#navBtn2").removeClass("bulletbgover").addClass("bulletbgpass"); ;
    $("#navBtn3").removeClass("bulletbg").addClass("bulletbgover"); ;
    $("#navTxt2").removeClass("active");
    $("#navTxt3").addClass("active");
}

function SetCustomerDetail() {
    var urlMethod = getUrlMethod("book.aspx", "SetCustomerDetail");
    var jsonData = "{}";

    callbackSubscription.Subscribe();
    SendAjax(urlMethod, jsonData, ReturnSetCustomerDetail);
}

function ReturnSetCustomerDetail(msg) {

    isBookingCom = msg.d.IsBooking;
    isBE3 = msg.d.IsBE3;
    isSuppressRewards = msg.d.IsSuppressRewards;

    // show the rewards panel.
    if (isBookingCom || isBE3 || isSuppressRewards) {
        $("#bkg_divRewards").hide();
        ab1788.hasRewards = false;
    }
    else {
        $("#bkg_divRewards").show();
    }

    GetCountryList();


    GetIssueBankCountry();


    isguestall = msg.d.ShowAllGuest;
    isRequiredTitle = msg.d.ShowAllGuest || msg.d.RequireTitle;

    //hide show Title of each guests
    $("[id^=divTitle]").each(function () {
        var anchor = $(this);
        if (msg.d.ShowAllGuest || msg.d.RequireTitle) {
            anchor.show();
            anchor.siblings().addClass('width-half-withTitle').removeClass('width-half');
        }
        else {
            anchor.hide();
        }
    });

    if (msg.d.ShowAllGuest) {
        $("#divChkNotMe").hide();
        $("#divguestName").show();

        guestNo = msg.d.Guests.length;
    }

    if (msg.d.IsDiscountCodeAllow) {
        $("#bkg_divDiscount").show();
    } else {
        $("#bkg_divDiscount").hide();
    }

    var str = "";
    for (var i = 0; i < msg.d.Guests.length; i++) {
        //Create the element first.
        if (i > 0) {
            if (msg.d.ShowAllGuest) {
                str += '<div class="bkg_divInputRow clear"><div class="nooverflow">';
                str += '<div class="bkg_divInputCol width-title" id="divTitle_' + i + '" ><span class="bkg_lblInput blackbold" >' + titleTxt + '</span>' +
                            '<div class="relative"><select id="ddlTitle_' + i + '" name="ddlTitle_' + i + '">';

                if (!msg.d.Guests[i].IsAdult)
                    str += '<option value="Child">Child</option>';
                str += "</select></div></div>";
                str += "<div class='bkg_divInputCol width-half-withTitle' id='bkg_divFirstname_" + i + "'><span class='bkg_lblInput blackbold'>" + firstNameTxt + "</span><div class='relative'><input id='txtFirstName_" + i + "' name='txtFirstName_" + i + "' class='width-half-withTitle agRequiredGuestName agFullName_" + i + "' type='text' maxlength='64' onblur='ValidateGuestName(" + i + ");' /></div></div>";
                str += "<div class='bkg_divInputCol width-half-withTitle' id='bkg_divLastname_" + i + "'><span class='bkg_lblInput blackbold'>" + lastNameTxt + "</span><div class='relative'><input id='txtLastName_" + i + "' name='txtLastName_" + i + "' class='width-half-withTitle agRequiredGuestName agFullName_" + i + "' type='text' maxlength='64' onblur='ValidateGuestName(" + i + ");' /></div></div>";
                str += '</div></div>';
            }

            // Need age of child dropdown...
            if (!msg.d.Guests[i].IsAdult) {

                var age = "";
                //TT123(T2)-1316
                if (is1316) {

                var childAgeFrom = msg.d.HotelExtrabedPolicy.DisplayedConsideredChildrenAgeFrom;
                var childAgeTo = msg.d.HotelExtrabedPolicy.DisplayedConsideredChildrenAgeTo;
                if (childAgeFrom == 0 || childAgeTo == 0) {
                    //no these information for specific hotel - we will set to default value like showing in grey bar of RoomTypeListGrid in the website(Children(2-11))
                    childAgeFrom = 2;
                    childAgeTo = 11;
                }
                age = "<option value='-1'>" + selectTxt + "</option><option value='" + (childAgeTo + 1) + "'>" + (childAgeTo + 1) + "+</option>";

                if (childAgeFrom < childAgeTo) {
                    for (var j = childAgeTo; j >= childAgeFrom; j--) {
                        age += "<option value='" + j + "'>" + j + "</option>";
                    }
                }
                }
                else {
                    age = "<option value='-1'>" + selectTxt + "</option><option value='17'>17+</option>";
                    for (var j = 16; j > 1; j--) {
                        age += "<option value='" + j + "'>" + j + "</option>";
                }

                }

                str += '<div class="bkg_divInputRow  clear" id="pnlAgeofChild_' + i + '"><div class="nooverflow">';
                str += '<div class="bkg_divInputCol pnlmouseoverAgeofChild" id="divAgeofChild_' + i + '">';

                str += '<span class="bkg_lblInput blackbold" >' + ageOfChildTxt + '</span>' +
                        "<div class='relative width-title'><select id='ddlAge_" + i + "' name='" + i + "'  class='ui-ddlAge agChildAge' >" + age + "</select></div>";
                //question mark style=""
                str += '<div class="ico_qstion absolute">' +
                        '<div class="iconquestion" id="imgIcon_AgeofChild_' + i + '"><span class="inline-block sprite ic-question" style="*height:auto"></span>' +
                            '<div id="divAgeofChildPopup_' + i + '" class="popup_body popup_body_left" style="display: none;">' +
                                '<div class="popup_header_promotion" >' +
                                    '<p><span class="inline-block sprite ic-title-popup"></span>' + cmsAgeofChildH + '</p>' +
                                '</div>' +
                                '<div class="popup_content_promotion" > <span style="text-decoration: none;" >' + cmsAgeofChild + '</span>' +
                                '</div>' +
                            '</div>' +
                            '<div class="calloutDown" style="display: none;" id="divAgeofChildCallout_' + i + '">' +
                                '<div class="calloutDown2" ></div>' +
                            '</div>' +
                        '</div>' +
                    '</div>';
                //end question mark
                str += "</div>";
                str += '<div class="bkg_divInputCol hinttext"><div class=" " id="divAgeMessage_' + i + '"></div><div class=" " id="divExtraBedOffer_' + i + '"><input type="checkbox" id="optExtraBed_' + i + '" name="' + i + '" value="ExtraBed"><label for="divExtraBedOffer_' + i + '">' + requestExtraBedTxt + '</label></div></div></div></div>';

            }
        }

        $("#txtFirstName_" + i).val(msg.d.Guests[i].Firstname);
        $("#txtLastName_" + i).val(msg.d.Guests[i].Lastname);
        $("#ddlCountry_" + i).val(msg.d.Guests[i].NationalityID);
    }

    if (!msg.d.ShowAllGuest) {
        var needguest = $("#chknotme").is(":checked");
        if (needguest) {
            $("#guestHolder").hide();
            $("#guestHolder_2").html(str);
        } else {
            $("#guestHolder").show();
            $("#guestHolder").html(str);
        }
    } else {
        $("#guestHolder").hide();
        $("#guestHolder_2").html(str);
    }

    // Bind Event
    for (var i = 0; i < msg.d.Guests.length; i++) {
        $("#divExtraBedOffer_" + i).hide();
        $("#ddlAge_" + i).change(function (e) {
            var urlMethod = getUrlMethod("book.aspx", "SetChildAge");
            var jsonData = "{'index' : " + $(this).attr('name') + ", 'age' : " + $(this).val() + "}";
            SendAjax(urlMethod, jsonData, ReturnSetChildAge);

            $("[id^=optExtraBed_]").prop("checked", false);
        });

        $("#optExtraBed_" + i).change(function (e) {
            var urlMethod = getUrlMethod("book.aspx", "RequestExtraBed");
            var jsonData = "{'index' : " + $(this).attr('name') + ", 'value' : " + $(this).is(":checked") + "}";
            SendAjax(urlMethod, jsonData, ReturnRequestExtraBed);
        });
    }

    if (msg.d.IsBooking) {
        $("#pnlAddress").show();
        $("#txtPhoneNo").removeClass("agPhone").addClass("agBookingComPhone");
    } else {
        $("#pnlAddress").hide();
    }

    if (msg.d.IsOccupancyFreeSearch && msg.d.IsMaxOccupancyRoom && msg.d.HasExtrabedCharge) {
        $("#pnlExtrabedOccFree").show();
    } else {
        $("#pnlExtrabedOccFree").hide();
    }

    //Show/hide separated Fligh Number
    var pnl = $("#pnlFlightNo");
    var pnlh = $("#divAirportTrans")
    if (msg.d.ShowFlightNo) {
        pnl.show();
        pnlh.hide();
    }
    else {
        pnl.hide();
        pnlh.show();
    }

    if (isRequiredTitle) {
        GetTitleList();
    }

    //bind validator for dynamic fields (multiple guests)    
    var ddlSelector = '[id^=ddlTitle], [id^=ddlAge], [id^=ddlCountry], #ddlCntctCountry';
    $(ddlSelector).each(function () {
        $(this).on('change', function () {
            $(this).valid();
        });
    });

    var validatees = $('#divguestName, #divPaymentDetail').find('input[type=text]:visible, select:visible');
    validatees.one('focus', function () {
        $('.guest_0').valid();
        validatees.off('focus');
    });

    AssignHoverDyn("AgeofChild");

    $("#ddlPaymentMethod").val(msg.d.Creditcard.CreditcardType);

    callbackSubscription.Unsubscribe();
}

function ReturnSetChildAge(msg) {
    if (msg.d.IsSuccess) {
        // Clear the message
        $("[id^=divAgeMessage]").html('').hide();
        $("[id^=divExtraBedOffer]").hide();


        for (var j = 0; j < msg.d.Index.length; j++) {
            $("#divAgeMessage_" + (msg.d.Index[j] - 1)).html(msg.d.Message).show();
        }
        for (var k = 0; k < msg.d.OfferExtraBedIndex.length; k++) {
            $("#divExtraBedOffer_" + (msg.d.OfferExtraBedIndex[k] - 1)).show();
        }

        GetBookingDetail();
    }
}

function AssignHoverDyn(obj) {
    if ($("[id^=imgIcon_" + obj + "]").size() != null || $("[id^=imgIcon_" + obj + "]").size() != 0) {
        $("[id^=imgIcon_" + obj + "]").each(function () {
            var id = this.id.replace("imgIcon_" + obj, "");
            var closeevent = function () {
                $("#div" + obj + "Popup" + id).hide();
                $("#div" + obj + "Callout" + id).hide();
            };
            //Booking Contions - dynamic Question mark icon hover show/hide popup    
            $("#imgIcon_" + obj + id + ", #lnkHover_" + obj + id).hover(
                function () {
                    var popup = $("#div" + obj + "Popup" + id).show();
                    $("#div" + obj + "Callout" + id).show();
                }, closeevent);
        });
    }
}

function GetCountryList() {
    var urlMethod = getUrlMethod("book.aspx", "GetCountryList");
    var jsonData = "{'languageId' : " + languageId + "}";
    SendAjaxSync(urlMethod, jsonData, ReturnGetCountryList);
}

function ReturnGetCountryList(msg) {
    var listItems = "<option value='0'>" + selectOneTxt + "</option>";

    for (var i = 0; i < msg.d.length; i++) {
        listItems += "<option value='" + msg.d[i].Key + "'>" + msg.d[i].Value + "</option>";
    }

    for (var j = 0; j < guestNo; j++) {
        $("#ddlCountry_" + j).html(listItems);
    }

        $("#ddlCntctCountry").html(listItems);
    }

function GetIssueBankCountry() {
    var urlMethod = getUrlMethod("book.aspx", "GetCountryList_V2");
    var jsonData = "{'languageId' : " + languageId + "}";
    SendAjaxSync(urlMethod, jsonData, ReturnGetIssueBankCountry);
}

function ReturnGetIssueBankCountry(msg) {
    var listItems = "<option value='0' name=''>" + selectOneTxt + "</option>";
    for (var i = 0; i < msg.d.length; i++) {
        listItems += "<option value='" + msg.d[i].CountryId + "' name='" + msg.d[i].CountryName + "'>" + msg.d[i].CountryTranslated + "</option>";
    }

    $("#ddlIssueBankCountry").html(listItems);
}

function GetTitleList() {
    var urlMethod = getUrlMethod("book.aspx", "GetTitleList");
    var jsonData = "{}";
    SendAjax(urlMethod, jsonData, ReturnGetTitleList);
}

function ReturnGetTitleList(msg) {
    var listItems = ""; // "<option value=''>" + selectTxt + "</option>";

    for (var i = 0; i < msg.d.length; i++) {
        listItems += "<option value='" + msg.d[i] + "'>" + msg.d[i] + "</option>";
    }

    $("#ddlTitleCnt").html("");
    $("#ddlTitleCnt").html(listItems);

    for (var i = 0; i < guestNo; i++) {
        if ($("#ddlTitle_" + i).val() != "Child") {
            $("#ddlTitle_" + i).html("");
            $("#ddlTitle_" + i).html(listItems);
        }
    }
}

function GetPaymentMethodList() {

    var urlMethod = getUrlMethod("book.aspx", "GetPaymentMethodList");
    var jsonData = "{'languageId' : " + languageId + "}";
    SendAjaxSync(urlMethod, jsonData, ReturnGetPaymentMethodList);
}

function ReturnGetPaymentMethodList(msg) {
    var listItems = "<option value='0' redirect='false'>" + pleaseSelect + "</option>";
    var listLogos = "";
    var listLogosPL = "";

    if (is1712) ab1712.paymentMethodList = msg.d || [];

    for (var i = 0; i < msg.d.length; i++) {
        if (msg.d[i].Id == 11 && !is1617)
            continue;

        if (is1712 && $("#payOpt2").prop("checked")) {
            if (!msg.d[i].IsRedirect) {
                listItems += "<option value='" + msg.d[i].Id + "' redirect='" + msg.d[i].IsRedirect + "'>" + msg.d[i].Name + "</option>";
            }
        } else {
            listItems += "<option value='" + msg.d[i].Id + "' redirect='" + msg.d[i].IsRedirect + "'>" + msg.d[i].Name + "</option>";
        }

        if (msg.d[i].Logo == true) {
            if (is1712) {
                listLogos += "<li class='inline-block logoPaymentMethod" + msg.d[i].Id + "' title='" + msg.d[i].Name + "'></li>";

                if (!(msg.d[i].IsRedirect || msg.d[i].Id == 6)) {
                    listLogosPL += "<li class='inline-block logoPaymentMethod" + msg.d[i].Id + "' title='" + msg.d[i].Name + "'></li>";
                }
            } else {
                listLogos += "<li style='float:left;' class='logoPaymentMethod" + msg.d[i].Id + "' title='" + msg.d[i].Name + "'>" + msg.d[i].Name + "</li>";
            }
        }
    }

    $("#ddlPaymentMethod").html(listItems);
    
    $(".ulcardslogo").html(listLogos);

    if (is1712) {
        $(".ulpllogo").html(listLogosPL);
    } 

    if (is1712) {
        var elems = $('#divPayment input[type="text"], #divPayment select:not("#ddlPaymentMethod")');
        $("#ddlPaymentMethod").val(0).add(elems).each(function () {
            $(this).removeClass("error valid")
                .siblings().filter('.error-icon, .valid-icon').remove();
            $(this).closest('.bkg_divInputCol').find('.ico_qstion').eq(0).removeClass('withValidateOffset');
        });
        ClearPaymentForm();
        SetTriggerPayment();
        $('#errPaymentMethod').empty();
    } else {
        $("#ddlPaymentMethod").val(0).change();
    }
}

function GetPromotions() {
    // Do not apply any discount when the payment model is payhotel or hotelbooking.
    if (!isBookingCom && !isBE3) {
        var creditCardNumber;
        // AMEX
        if ($("#ddlPaymentMethod").val() == "4") {
            creditCardNumber = $("#txtAmex_0").val() + $("#txtAmex_1").val() + $("#txtAmex_2").val();
            $("#txtIssueBank").val("American Express");
        } else if ($("#ddlPaymentMethod").val() == "11") {
            creditCardNumber = $("#txtDiners_0").val() + $("#txtDiners_1").val() + $("#txtDiners_2").val();
        } else {
            creditCardNumber = $("#txtCard_0").val() + $("#txtCard_1").val() + $("#txtCard_2").val() + $("#txtCard_3").val();
        }

        var urlMethod = getUrlMethod("book.aspx", "GetPromotions");
        var jsonData = "{'promoCode' : '" + $("#bkg_txtDiscountCode").val() + "', 'email' : '" + $("#txtEmail").val().replace("\'", "") + "', 'creditCard' : '" + creditCardNumber + "'}";

        callbackSubscription.Subscribe();
        SendAjaxSync(urlMethod, escape(jsonData), ReturnGetPromotions);

    }
}

function ReturnGetPromotions(msg) {
    if (msg.d == null)
        return;

    $("#divPromoResponseMessage").html(msg.d.Message);
    if (msg.d.HasCreditCardPromotion) {
        if (msg.d.MemberShipContent != "") {
            $("#divPhoenix").show();
            $("#spanMembershipContent").html(msg.d.MemberShipContent);
            $("#txtPhoenix").prop('disabled', false);
        } else {
            if ($("#spanMembershipContent")[0].innerHTML != "") {

                if ($("#txtPhoenix").prop('disabled') == false) {
                    $("#txtPhoenix").prop('disabled', true);
                }
            }
        }

    }

    callbackSubscription.Unsubscribe();

    GetBookingDetail();
}

function GetFilledDetail() {
    var urlMethod = getUrlMethod("book.aspx", "GetFilledDetail");
    var jsonData = "{}";
    SendAjax(urlMethod, jsonData, ReturnGetFilledDetail);
}

function ReturnGetFilledDetail(msg) {
    $("#ddlPaymentMethod").val(msg.d.CreditCard.CreditcardType);

    SetTriggerPayment();
    UpdatePayment();
    var cardno = "";

    $("#txtHolderName").val(msg.d.CreditCard.CardholderName);

    // AMEX
    if ($("#ddlPaymentMethod").val() == "4") {
        $("#txtAmex_0").val(msg.d.CreditCard.Amex0);
        $("#txtAmex_1").val(msg.d.CreditCard.Amex1);
        $("#txtAmex_2").val(msg.d.CreditCard.Amex2);
        cardno = $('#txtAmex_0').val() + $('#txtAmex_1').val() + $('#txtAmex_2').val();
    } else if ($("#ddlPaymentMethod").val() == "11") {
        $("#txtDiners_0").val(msg.d.CreditCard.Diners0);
        $("#txtDiners_1").val(msg.d.CreditCard.Diners1);
        $("#txtDiners_2").val(msg.d.CreditCard.Diners2);
        cardno = $('#txtDiners_0').val() + $('#txtDiners_1').val() + $('#txtDiners_2').val();
    } else {
        $("#txtCard_0").val(msg.d.CreditCard.Card0);
        $("#txtCard_1").val(msg.d.CreditCard.Card1);
        $("#txtCard_2").val(msg.d.CreditCard.Card2);
        $("#txtCard_3").val(msg.d.CreditCard.Card3);
        cardno = $('#txtCard_0').val() + $('#txtCard_1').val() + $('#txtCard_2').val() + $('#txtCard_3').val();
    }

    $("#hidCardNo").val(cardno);
    $("#txtCvc").val(msg.d.CreditCard.SecurityCode);

    if (msg.d.CreditCard.ExpiryMonth != "") {
        $("#ddlExpiryMonth").val(msg.d.CreditCard.ExpiryMonth);
    }

    if (msg.d.CreditCard.ExpiryYear != "") {
        $("#ddlExpiryYear").val(msg.d.CreditCard.ExpiryYear);
    }

    $("#ddlIssueBankCountry").val(msg.d.CreditCard.IssueBankCountryId);
    $("#txtIssueBank").val(msg.d.CreditCard.IssueBank);

    $("#txtCntFirstName").val(msg.d.Customer.FirstName);
    $("#txtCntLastName").val(msg.d.Customer.LastName);
    $("#txtEmail").val(msg.d.Customer.Email);


    if (typeof msg.d.Customer.CountryId === 'undefined') {
            $("#ddlCntctCountry").val("0");
    } else {
        var countryid = msg.d.Customer.CountryId;
            $("#ddlCntctCountry").val(countryid);
    }

    $("#ddlCountry_0").val("0");

    $("#txtPhoneNo").val(msg.d.Customer.PhoneNo);

    if (msg.d.Customer.Newsletter) {
        $("#chkContactSendMe").prop("checked", true);
    }

    //Special Needs
    var specialNeed = msg.d.SpecialNeed;

    $("#txtFlightNo").val(specialNeed.ArrivalFlightNo);
    $("#txtDeFlightNo").val(specialNeed.DepartFlightNo);

    $("#chkNonSmoking").prop("checked", specialNeed.IsNonSmoke);
    $("#chkLateChkin").prop("checked", specialNeed.LateCheckIn);
    $("#chkEarlyChkin").prop("checked", specialNeed.EarlyCheckIn);
    $("#chkHighFloor").prop("checked", specialNeed.HighFloor);
    $("#chkLargeBed").prop("checked", specialNeed.LargeBed);
    $("#chkTwinBed").prop("checked", specialNeed.TwinBeds);
    $("#txtAdditionalNotes").val(specialNeed.AdditionalNotes);
    if (specialNeed.AirportTransfer != "" && specialNeed.AirportTransfer != null) {
        $("#chkAirportTrans").prop("checked", true);
        $("#bkg_txtFightNoArrivalTime").val(specialNeed.AirportTransfer);
    }
    else {
        $("#chkAirportTrans").prop("checked", false);
    }

    if (errGAT == 425) {
        $("#txtConfirmEmail").val(msg.d.Customer.Email);
        //        isguestall = msg.d.ShowAllGuest;
        //        isRequiredTitle = msg.d.ShowAllGuest || msg.d.RequireTitle;

        if (isguestall) {
            for (var i = 0; i < msg.d.Guests.length; i++) {
                // arrayGuest.push({ Title: $("#ddlTitle_" + i).val(), FirstName: $.trim($("#txtFirstName_" + i).val()), LastName: $.trim($("#txtLastName_" + i).val()), NationalId: $("#ddlCountry_" + i).val() });
                $("#ddlTitle_" + i).val(msg.d.Guests[i].Title);
                $("#txtFirstName_" + i).val(msg.d.Guests[i].FirstName);
                $("#txtLastName_" + i).val(msg.d.Guests[i].LastName);
                $("#ddlCountry_" + i).val(msg.d.Guests[i].NationalId);
            }
        } else {

            if (msg.d.Guests[0].FirstName != msg.d.Customer.FirstName || msg.d.Guests[0].LastName != msg.d.Customer.LastName) {
                //$('#chknotme').trigger('click');
                $("#chknotme").prop("checked", true);

                $('#divguestName').show();
                $("#guestHolder").hide();

                //$('#chknotme').trigger('click');
            }

            if (isRequiredTitle) {
                $("#ddlTitle_0").val(msg.d.Guests[0].Title);
            }

            $("#txtFirstName_0").val(msg.d.Guests[0].FirstName);
            $("#txtLastName_0").val(msg.d.Guests[0].LastName);
            $("#ddlCountry_0").val(msg.d.Guests[0].NationalId);
        }
    }

    if (errMsgFindPaymentGatewayFail != null && errMsgFindPaymentGatewayFail != "") {
        SetPaymentGatewayFail(errMsgFindPaymentGatewayFail);
    }

    //var $excElem = $('input:text[value=""], select.ignore, textarea, #bkg_divRewards input, #divPayment .ignore');
    //$('select:visible').each(function () {
    //    if (+($(this).val()) <= 0) {
    //        $excElem = $excElem.add($(this));
    //    }
    //});
    //ValidateFormStep1($excElem);
}

function UpdatePayment() {
    $("#ddlPaymentMethod").change(function () {
        ClearPaymentForm();
        SetTriggerPayment();

        cctxt1 = false;
        cctxt2 = false;
        cctxt3 = false;
        cctxt4 = false;

        if ($("#ddlPaymentMethod").val() == "4") {
            $("#txtAmex_0").focus();
        } else if ($("#ddlPaymentMethod").val() == "11") {
            $("#txtDiners_0").focus();
            //} else if ($("#ddlPaymentMethod").val() != "4" && $("#ddlPaymentMethod").val() != "5") {
        } else if ($("#ddlPaymentMethod").val() == "1" || $("#ddlPaymentMethod").val() == "2" || $("#ddlPaymentMethod").val() == "3" || $("#ddlPaymentMethod").val() == "6") {
            $("#txtCard_0").focus();
        }

        GetPromotions();

        if (is1751 && $(this).val() != 0) {
            var isRedirect = false;
            isRedirect = ($("#ddlPaymentMethod option[value='" + $(this).val() + "']").attr("redirect") === 'true');
            ab1751.SetupStep2(isRedirect);
        }
    });
}

function ClearPaymentForm() {
    $("#txtCard_0, #txtCard_1, #txtCard_2, #txtCard_3, #txtAmex_0, #txtAmex_1, #txtAmex_2, #txtDiners_0, #txtDiners_1, #txtDiners_2, #txtHolderName, #txtCvc, #txtIssueBank, #hidCardNo").val("");
    $("#ddlExpiryMonth, #ddlExpiryYear, #ddlIssueBankCountry").val(0);
    $("#errPayment_1, #errPayment_2, #errPayment_3, #errPayment_4").empty();

    $('#errCardNo, #errCardHolderName, #errExpiryDate, #errCVC, #errIssueBankCountry, #errIssueBank').empty();

    if (is1751) {
        ab1751.ClearChargeMeIn();
    }
}

function SetTriggerPayment() {
    var sel = $("#ddlPaymentMethod").val();
    var redirect = $("#ddlPaymentMethod option[value='" + sel + "']").attr("redirect");

    if (isBookingCom) {
        $("#bkg_divCardNo, #bkg_divCardHolderName").show();
        $("#bkg_divCardExpiry,#bkg_divCVCNo,").show();
        $("#bkg_divCardNoAmex").hide();
        $("#bkg_divCardNoDiners").hide();
        $("#bkg_divWhichBank, #bkg_divCountryIssueBank").hide();

        $("#bkg_rowPayment_3").hide();

        if (sel == "0") {
            $("#bkg_divCardNoAmex").hide();
            $("#bkg_divCardNoDiners").hide();
        }else if (sel == "4") {
            $("#bkg_divCardNo").hide();
            $("#bkg_divCardNoDiners").hide();
            $("#bkg_divCardNoAmex").show();
        } else if (sel == "11") {
            $("#bkg_divCardNo").hide();
            $("#bkg_divCardNoAmex").hide();
            $("#bkg_divCardNoDiners").show();
        }

        if (redirect == "true") {
            $("#bkg_divCardNo, #bkg_divCardNoAmex, #bkg_divCardHolderName").hide();
            $("#bkg_divCardExpiry,#bkg_divCVCNo").hide();
        }
    }
    else if (isBE3) {
        $("#bkg_divCardNo, #bkg_divCardHolderName").show();
        $("#bkg_divCardExpiry,#bkg_divCVCNo,").show();
        $("#bkg_divCardNoAmex").hide();
        $("#bkg_divCardNoDiners").hide();
        $("#bkg_divCVCNo").hide(); //BE3 needs CVC - TBC
        $("#bkg_divCountryIssueBank, #bkg_divWhichBank").show();
        $("[id^=bkg_divcards_2]").hide();

        if (sel == "0") {
            $("#bkg_divCardNoAmex, #bkg_divCountryIssueBank, #bkg_divWhichBank, #bkg_divCardNoDiners").hide();
        }else if (sel == "4") {
            $("#bkg_divCardNo").hide();
            $("#bkg_divCardNoDiners").hide();
            $("#bkg_divCardNoAmex").show();
            $("#bkg_divCountryIssueBank").show();
            $("#bkg_divWhichBank").hide();
        } else if (sel == "11") {
            $("#bkg_divCardNo").hide();
            $("#bkg_divCardNoAmex").hide();
            $("#bkg_divCardNoDiners").show();
        }

        if (redirect == "true") {
            $("#bkg_divCardNo, #bkg_divCardNoAmex, #bkg_divCardNoDiners, #bkg_divCardHolderName").hide();
            $("#bkg_divCardExpiry,#bkg_divCVCNo,#bkg_divCountryIssueBank").hide();
            $("#bkg_divWhichBank").hide();
        }
    }
    else { //normal booking form

        $("#bkg_divCardNo, #bkg_divCardHolderName").show();
        $("#bkg_divCardExpiry,#bkg_divCVCNo,#bkg_divCountryIssueBank, #bkg_divWhichBank").show();
        $("#bkg_divCardNoAmex, #bkg_divCardNoDiners").hide();

        if (sel == "0") {
            $("#bkg_divCardNoAmex, #bkg_divCardNoDiners, #bkg_divCountryIssueBank, #bkg_divWhichBank").hide();
        }else if (sel == "4") {
            $("#bkg_divCardNo, #bkg_divWhichBank, #bkg_divCardNoDiners").hide();
            $("#bkg_divCardNoAmex").show();
        } else if (sel == "11") {
            $("#bkg_divCardNo, #bkg_divCardNoAmex").hide();
            $("#bkg_divCardNoDiners").show();
        }

        if (redirect == "true") {
            $("#bkg_divCardNo, #bkg_divCardNoAmex, #bkg_divCardNoDiners, #bkg_divCardHolderName").hide();
            $("#bkg_divCardExpiry,#bkg_divCVCNo,#bkg_divCountryIssueBank").hide();
            $("#bkg_divWhichBank").hide();

            $("#errPayment_3").empty();
        }
    }
    ClearPaymentForm();
}

function BindExpiryMonth() {

    $("#ddlExpiryMonth").html("");

    var listItems = "<option value='0'>mm</option>";
    for (var i = 1; i < 13; i++) {

        var month = '';
        if (i < 10)
            month = '0' + i;
        else
            month = i;

        listItems += "<option value='" + month + "'>" + month + "</option>";
    }
    $("#ddlExpiryMonth").html(listItems);
}

function BindExpiryYear() {

    $("#ddlExpiryYear").html("");

    var listItems = "<option value='0'>yyyy</option>";
    var d = new Date();
    var curr_year = d.getFullYear();
    for (var i = curr_year; i <= (curr_year + 10); i++) {
        listItems += "<option value='" + i + "'>" + i + "</option>";
    }
    $("#ddlExpiryYear").html(listItems);
}

function Submitbooking() {

    if (isagent) {
        ContinueSubmitBooking();
    } else {
        var excludedElems = $('input.ignore:text[value=""], select.ignore, textarea, #bkg_divRewards input, #divPayment .ignore');
        if ($('#ddlPaymentMethod').val() != 0) {
            cardvalidated = true;
            expiryvalidated = true;
        }

        if ($('input[type=text]:visible, select:visible').not(excludedElems).valid()) {
            // Normal case.
            ContinueSubmitBooking();
            //}
        }
        if ($('.error:visible').length) {
            $('html, body').animate({
                scrollTop: $('.error:visible').eq(0).offset().top - 24
            }, 500);
            $('.error:visible').eq(0).focus();
        }
    }
}

function ContinueSubmitBooking() {

    var urlMethod = getUrlMethod("book.aspx", "SubmitStep");

    var phoenixText = "";
    if ($("#txtPhoenix").prop('disabled') == false) {
        phoenixText = $.trim($("#txtPhoenix").val());
    }

    //customer
    var customer = { FirstName: $.trim($("#txtCntFirstName").val()), LastName: $.trim($("#txtCntLastName").val()), CountryId: $("#ddlCntctCountry").val(), Email: $.trim($("#txtEmail").val()),
        ConfirmEmail: $.trim($("#txtEmail").val()), PhoneNo: $.trim($("#txtPhoneNo").val()), Newsletter: $("#chkContactSendMe").is(":checked"),
        Address1: $.trim($("#txtAddress").val()), Address2: "", City: $.trim($("#txtCity").val()), Postal: $.trim($("#txtPostal").val()), CountryId: $("#ddlCntctCountry").val(),
        MembershipContentText: phoenixText
    };

    var needguest = $("#chknotme").is(":checked");
    var title0 = "";
    var arrayGuest = [];

    if (needguest || isguestall) {

        if (isRequiredTitle)
            title0 = $("#ddlTitle_0").val();

        arrayGuest = [{ Title: title0, FirstName: $.trim($("#txtFirstName_0").val()), LastName: $.trim($("#txtLastName_0").val()), NationalId: $("#ddlCountry_0").val()}];

        // Add another guests.
        for (var i = 1; i < guestNo; i++) {
            arrayGuest.push({ Title: $("#ddlTitle_" + i).val(), FirstName: $.trim($("#txtFirstName_" + i).val()), LastName: $.trim($("#txtLastName_" + i).val()), NationalId: $("#ddlCountry_" + i).val() });
        }

        var guests = { "guests": arrayGuest };
    } else {

        if (isRequiredTitle)
            title0 = $("#divTitleCnt").val();

        arrayGuest = [{ Title: title0, FirstName: $.trim($("#txtCntFirstName").val()), LastName: $.trim($("#txtCntLastName").val()), NationalId: $("#ddlCntctCountry").val()}];

        var guests = { "guests": arrayGuest };
    }


    var creditCardNumber;
    // AMEX
    if ($("#ddlPaymentMethod").val() == "4") {
        creditCardNumber = $("#txtAmex_0").val() + $("#txtAmex_1").val() + $("#txtAmex_2").val();
        $("#txtIssueBank").val("American Express");
    } else if ($("#ddlPaymentMethod").val() == "11") {
        creditCardNumber = $("#txtDiners_0").val() + $("#txtDiners_1").val() + $("#txtDiners_2").val();
    } else {
        creditCardNumber = $("#txtCard_0").val() + $("#txtCard_1").val() + $("#txtCard_2").val() + $("#txtCard_3").val();
    }

    var today = new Date();

    if (is1712 && typeof chargedate !== 'undefined') {
        today = new Date(chargedate);
    }     

    var creditCard = { CreditcardType: $("#ddlPaymentMethod").val(),
        CreditCardNumber: creditCardNumber,
        CardholderName: $.trim($("#txtHolderName").val()), ExpiryDate: $("#ddlExpiryMonth").val() + "/" + $("#ddlExpiryYear").val(),
        SecurityCode: $("#txtCvc").val(), IssueBankCountryId: $("#ddlIssueBankCountry").val(), IssueBank: $.trim($("#txtIssueBank").val()), ChargeOption: $("#payOpt2").prop("checked"), FullyChargeDate: today
    };

    var airportTransfer = '';
    if ($("#chkAirportTrans").is(":checked")) {
        if ($("#bkg_txtFightNoArrivalTime").val() != cmsEnterFlightHint) {
            airportTransfer = $.trim($("#bkg_txtFightNoArrivalTime").val());
        }
    }

    var specialNeed = '';

    specialNeed = { ArrivalFlightNo: $.trim($("#txtFlightNo").val()), DepartFlightNo: $.trim($("#txtDeFlightNo").val()), IsNonSmoke: $("#chkNonSmoking").is(":checked"), LateCheckIn: $("#chkLateChkin").is(":checked"), EarlyCheckIn: $("#chkEarlyChkin").is(":checked"), HighFloor: $("#chkHighFloor").is(":checked"), LargeBed: $("#chkLargeBed").is(":checked"), TwinBeds: $("#chkTwinBed").is(":checked"), AirportTransfer: airportTransfer, AdditionalNotes: $.trim($("#txtAdditionalNotes").val()) };

    var jsonData = "{'guests' : '" + JSON.stringify(guests) + "', 'creditcard' : ' " + JSON.stringify(creditCard) + "', 'customer' : ' " + JSON.stringify(customer) + "', 'specialneed' : '" + JSON.stringify(specialNeed) + "'}";
 
    SendAjax(urlMethod, escape(jsonData), ReturnContinueSubmitBooking);
}

function CheckPromotion() {

    if ($("#bkg_txtDiscountCode").val() != "") {
        var urlMethod = getUrlMethod("book.aspx", "CheckPromotions");
        var jsonData = "{'promoCode' : '" + $("#bkg_txtDiscountCode").val() + "', 'email' : '" + $("#txtEmail").val().replace("\'", "") + "'}";
        SendAjax(urlMethod, escape(jsonData), ReturnCheckPromotion);
    }
    else {
        $("#divPromoResponseMessage").html("");
    }
}

function ReturnCheckPromotion(msg) {
    $("#divPromoResponseMessage").html(msg.d.Message);
    GetBookingDetail();
    if (msg.d.IsSuccess) {
        // submit step 1, and go to step 2
        //   ContinueSubmitBooking();
        SubmitFirstStep();
    }
}

function ReturnContinueSubmitBooking(msg) {   
    $("[id^=err]:visible").empty();

    $("[id^=ddlAge_]").each(function () {
        if ($(this).val() == -1) {
            msg.d.ErrorList.push({ Index: 3, Type: 1, Message: ageOfChildRequired, TypeText: 'Guest' });
            return false;
        }
    });

    var visibleElems = "";
    var needguest = $("#chknotme").is(":checked") || isguestall;
    var err1383 = [];
    var firstEmpty = "";
    var paymenterr = false;
    var targetName = "#errSum";

    $("#errCard").html("");
    $(targetName).html("");

    for (var i = 0; i < msg.d.ErrorList.length; i++) {      
        
        if (msg.d.ErrorList[i].Type == 2) {
            paymenterr = true;
        }
        var target = "";

        if (is1383) {
            err1383.push(msg.d.ErrorList[i].ErrorNo + ":" + msg.d.ErrorList[i].Message + "");
        }

        if (msg.d.ErrorList[i].Type != 2 && msg.d.ErrorList[i].Index != 1) {
            $(targetName).append("<li>" + msg.d.ErrorList[i].Message + "</li>");
        } else {
            if (msg.d.ErrorPageUrl != null && msg.d.ErrorPageUrl != "") {
                disabledConfirm_exit = true;
                window.location = msg.d.ErrorPageUrl;
                return;
            } else {
                $("#errCard").append(msg.d.ErrorList[i].Message);
            }
        }
    }

   

    if ($("#errCard")[0].innerHTML.length > 0)
        $("#errCard").show();
        if (is1788) {
            $('html, body').animate({
                scrollTop: $('#errCard').eq(0).focus().offset().top
            }, 500);
        }
    else
        $("#errCard").hide();

    if (msg.d.ErrorList.length <= 0) {
        visibleElems = $("#box_left select:visible,#box_left input[type=text]:visible");
        visibleElems.each(function () {
            $(this).css("border-color", "#8D9AA3");
        });

        // Please wait...
        tb_show("DoBook", "#TB_inline?height=105&width=300&inlineId=pnlContinue2Popup&modal=true");
        CheckCurrency();

        if (is1712 && flag && !isPayLater && msg.d.ErrorList.length <= 0) {
            //string chargeDate, string errors, string payment
            jsonData = "{ 'chargeDate' : '" + chargedate + "','errors' : '" + errPL + "','payment' : '" + paymentMethodPL + "' }";
            SendAjaxSync("/b/SendGenericMessage.aspx/SendBackToPayLaterMessage?p=" + p, jsonData);
        }

    } else {
        if (paymenterr) {
            var sel = $("#ddlPaymentMethod").val();

            if (sel == "0") {
                $("#bkg_divCountryIssueBank, #bkg_divWhichBank").hide();
            } else if (sel == "4") {
                $("#bkg_divCardNo, #bkg_divWhichBank").hide();
                $("#bkg_divCardNoAmex, #bkg_divCountryIssueBank").show();

            } else if (sel == "11") {
                $("#bkg_divCardNoDiners, #bkg_divWhichBank, #bkg_divCountryIssueBank").show();
                $("#bkg_divCardNo, #bkg_divCardNoAmex").hide();
                $("#txtIssueBank").val("");

            }else if (sel != "5") {
                $("#bkg_divCardNo, #bkg_divWhichBank, #bkg_divCountryIssueBank").show();
                $("#bkg_divCardNoAmex").hide();
                $("#txtIssueBank").val("");

            }
        }
    }

    var jsonData = "";
    if (is1383) {
        var errmsg = '';
        var data = [];
        data.push('paymentId:' + $("#ddlPaymentMethod").val());
        data.push('noOfPaymentCtrl:' + $('#divPayment select:visible,#divPayment input[type=text]:visible').length);

        var first = $("#box_left input[value='']:input[type=text]:visible,select[value='0']:visible");

        if (first.length > 0) {
            data.push('empty field: ' + first[0].id);
        }

        if (err1383.length > 0) {
            var text = err1383.join(", ");
            data.push('err: ' + text);
        }

        errmsg = data.join("|");

        jsonData = "{ 'msg' : '" + errmsg + "' }";
        SendAjax("/b/ClientTechnoStatLog.aspx/LogSubmitStat?1=1", jsonData);
    }
        
    if (is1712 && flag && msg.d.ErrorList.length <= 0) {
        //string chargeDate, string errors, string payment
        jsonData = "{ 'chargeDate' : '" + chargedate + "','errors' : '" + errPL + "','payment' : '" + paymentMethodPL + "' }";
        SendAjax("/b/SendGenericMessage.aspx/SendBackToPayLaterMessage?p=" + p, jsonData);
    }
        
}

// Checks the currency.
function CheckCurrency() {
    var sel = $("#ddlPaymentMethod").val();
    var redirect = $("#ddlPaymentMethod option[value='" + sel + "']").attr("redirect");
    var urlMethod = getUrlMethod("book.aspx", "CheckCurrency");
    var jsonData = "{ 'isRedirect' : '" + redirect + "'}";
    SendAjax(urlMethod, jsonData, ReturnCheckCurrency);
}

function SetPaymentGatewayFail(errMsg) {
    $("#errCard").show();
    $("#errCard").append(errMsg);

    if (is1788) {
        $('html, body').animate({
            scrollTop: $('#errCard').eq(0).focus().offset().top
        }, 500);
    }
}

function SubmitFirstStepClicked() {
    if ($("#bkg_txtDiscountCode").val() != "") {
        CheckPromotion();
    } else {
        if (isGA == true) {
            _ga.cv36 = '2';

            _ga.vp = window.location.pathname + '/step2';
            _ga.setVP();

        }

        SubmitFirstStep();
    }
}

function SubmitFirstStep() {

    var urlMethod = getUrlMethod("book.aspx", "SubmitFirstStep");

    var phoenixText = "";
    if ($("#txtPhoenix").prop('disabled') == false) {
        phoenixText = $.trim($("#txtPhoenix").val());
    }

    //customer
    var customer = { FirstName: $.trim($("#txtCntFirstName").val()), LastName: $.trim($("#txtCntLastName").val()), CountryId: $("#ddlCntctCountry").val(), Email: $.trim($("#txtEmail").val()),
        ConfirmEmail: $.trim($("#txtEmail").val()), PhoneNo: $.trim($("#txtPhoneNo").val()), Newsletter: $("#chkContactSendMe").is(":checked"),
        Address1: $.trim($("#txtAddress").val()), Address2: "", City: $.trim($("#txtCity").val()), Postal: $.trim($("#txtPostal").val()), CountryId: $("#ddlCntctCountry").val(),
        MembershipContentText: phoenixText
    };

    var needguest = $("#chknotme").is(":checked");
    var title0 = "";
    var arrayGuest = [];

    if (needguest || isguestall) {

        if (isRequiredTitle)
            title0 = $("#ddlTitle_0").val();

        arrayGuest = [{ Title: title0, FirstName: $.trim($("#txtFirstName_0").val()), LastName: $.trim($("#txtLastName_0").val()), NationalId: $("#ddlCountry_0").val()}];

        // Add another guests.
        for (var i = 1; i < guestNo; i++) {
            arrayGuest.push({ Title: $("#ddlTitle_" + i).val(), FirstName: $.trim($("#txtFirstName_" + i).val()), LastName: $.trim($("#txtLastName_" + i).val()), NationalId: $("#ddlCountry_" + i).val() });
        }

        var guests = { "guests": arrayGuest };
    } else {

        if (isRequiredTitle)
            title0 = $("#ddlTitleCnt").val();

        arrayGuest = [{ Title: title0, FirstName: $.trim($("#txtCntFirstName").val()), LastName: $.trim($("#txtCntLastName").val()), NationalId: $("#ddlCntctCountry").val()}];

        var guests = { "guests": arrayGuest };
    }

    var airportTransfer = '';
    if ($("#chkAirportTrans").is(":checked")) {
        if ($("#bkg_txtFightNoArrivalTime").val() != cmsEnterFlightHint) {
            airportTransfer = $.trim($("#bkg_txtFightNoArrivalTime").val());
        }
    }
    var specialNeed = '';

    specialNeed = { ArrivalFlightNo: $.trim($("#txtFlightNo").val()), DepartFlightNo: $.trim($("#txtDeFlightNo").val()), IsNonSmoke: $("#chkNonSmoking").is(":checked"), LateCheckIn: $("#chkLateChkin").is(":checked"), EarlyCheckIn: $("#chkEarlyChkin").is(":checked"), HighFloor: $("#chkHighFloor").is(":checked"), LargeBed: $("#chkLargeBed").is(":checked"), TwinBeds: $("#chkTwinBed").is(":checked"), AirportTransfer: airportTransfer, AdditionalNotes: $.trim($("#txtAdditionalNotes").val()) };

    //var jsonData = "{'guests' : '" + JSON.stringify(guests) + "', 'creditcard' : ' " + JSON.stringify(creditCard) + "', 'customer' : ' " + JSON.stringify(customer) + "', 'specialneed' : '" + JSON.stringify(specialNeed) + "'}";
    var jsonData = "{'guests' : '" + JSON.stringify(guests) + "', 'customer' : ' " + JSON.stringify(customer) + "', 'specialneed' : '" + JSON.stringify(specialNeed) + "'}";

    SendAjax(urlMethod, escape(jsonData), ReturnSubmitFirstStep);
}

function ReturnSubmitFirstStep(msg) {

    if (msg.d.ErrorList.length == 0) {
        //$('#divHeadTitle')
        $("#div1712").hide();

        $("#errCard").empty();
        $("#divHeadTitle")[0].innerHTML = cmsPaymentDetail;

        $('#divstep1').hide();
        $('#btnContinue,#btnContinue1788').hide();

        $('#divstep2').show();
        $('#btnBack, #btnBack1788').show();
        $('#btnSubmit, #btnSubmit1788').show();

        SetupBlueButtons();

        if (isagent) {
            //     $('#divPayment').hide();
            jQuery.each($('#divPayment select:visible,#divPayment input[type=text]:visible'), function (i, elem) {
                $(elem).addClass('ignore');
                $(elem).prop("disabled", true);
            });
        }

        $('#pnlTotalPrice').show();

        if (is1693) {
            if (showcollected)
                $('#divExcludedTaxDetail').show();
            else
                $('#divExcludedTaxDetail').hide();
            $('#trFinalPrice').show();
        }
        else {
            if (isAppliedCB || (ispartAppliedCB && is1678))
                $('#notincluded').hide();
        }

        if (is1712) {
            ab1712.SetupStep2();
        }

        if (is1788) {
            $('html, body').animate({
                scrollTop: $('#logowrapper').eq(0).focus().offset().top
            }, 500);
            if ( ab1788.isPhoneView()) {
                $('#bkg_divRewards').hide();
            }
            $('#errSum').empty();
        }

        if ((is1807 && !ab1807.isChecked) || (is1808 && !ab1808.isChecked) || (is1824 && !ab1824.isChecked) || (is1825 && !ab1825.isChecked)) {
            ab1808.CheckAllotment();
        }

        if (is1788) {
            $('html, body').animate({
                scrollTop: $('#logowrapper').eq(0).focus().offset().top
            }, 500);
        }

        step = 2;
        return;
    }

    if (msg.d.ErrorPageUrl != null && msg.d.ErrorPageUrl != "") {
        disabledConfirm_exit = true;
        window.location = msg.d.ErrorPageUrl;
        return;
    }

    var targetName = "#errSum";
    $(targetName).html("");
    for (var i = 0; i < msg.d.ErrorList.length; i++) {
        $(targetName).append("<li>" + msg.d.ErrorList[i].Message + "</li>");
    }

}

function Switch1StepBookingFail() {
    $("#divHeadTitle")[0].innerHTML = cmsBookingDetail;

    $('#divstep1').show();
    $('#btnContinue, #btnContinue1788').show();

    $('#divstep2').hide();
    $('#btnBack, #btnBack1788').hide();
    $('#btnSubmit, #btnSubmit1788').hide();

    $('#pnlTotalPrice').hide();
    if (is1693) {
        $('#divExcludedTaxDetail').hide();
        $('#trFinalPrice').hide();
    }

    // $("#errSum").html(err);

    if (is1788) {
        $('html, body').animate({
            scrollTop: $('#logowrapper').eq(0).focus().offset().top
        }, 500);
    }

    step = 1;

    SetupBlueButtons();

    if (is1788) {
        $('html, body').animate({
            scrollTop: $('#logowrapper').eq(0).focus().offset().top
        }, 500);
        if (ab1788.hasRewards) {
            $('#bkg_divRewards').show();
}
    }
}

function Switch2StepPaymentFail(err) {
    $("#divHeadTitle")[0].innerHTML = cmsPaymentDetail;

    $('#divstep1').hide();
    $('#btnContinue').hide();

    $('#divstep2').show();
    $('#btnBack, #btnBack1788').show();
    $('#btnSubmit, #btnSubmit1788').show();

    $('#pnlTotalPrice').show();
    if (is1693) {
        if (showcollected)
            $('#divExcludedTaxDetail').show();
        else
            $('#divExcludedTaxDetail').hide();

        $('#trFinalPrice').show();
    }
    $("#errCard").html(errMsgFindPaymentGatewayFail);

    if (is1788) {
        $('html, body').animate({
            scrollTop: $('#errCard').eq(0).focus().offset().top
        }, 500);
        if (ab1788.isPhoneView()) {
            $('#bkg_divRewards').hide();
        }
    }

    step = 2;
}

function TurnOnAutoComplete() {

    jQuery.each($("#divCutName input[type=text]:not('#txtConfirmEmail'):visible, #divguestName input[type=text]"), function (i, elem) {
        elem.autocomplete = "on";
    });

    jQuery.each($("input:text[id^=txtFirst],[id^=txtLast], #divContact input[type=text]:not('#txtEmailConfirm')"), function (i, elem) {
        elem.autocomplete = "on";
    });

}

var callbackSubscription = function () {
    var firstRunFlag = true;
    var subscribers = 0;
    return {
        Subscribe: function () {
            if (firstRunFlag) {
                subscribers++;
            }
        },
        Unsubscribe: function () {
            if (firstRunFlag) {
                subscribers--;
                if (!subscribers) {
                    if ($('#divstep1:visible').length) {
                        $('#divBtnWrapperStep1').appendTo($('#divstep1 .bggreybox:visible').last());
                    }
                    firstRunFlag = false;
                }
            }
        }
    };
} ();

function SetupBlueButtons() {
    if ($('#divstep1:visible').length) {
        $('#divContBtn').hide();
        $('#box_left').off('keypress')
            .keypress(function (e) {
            if ((e.which && e.which == 13) || (e.keyCode && e.keyCode == 13)) {
                $(this).blur();
                $('#btnContinue').eq(0).click();
                return false;
            }
        });
    }
    else if ($('#divstep2:visible').length) {
        $('#divContBtn').show();
        $('#box_left').off('keypress')
            .keypress(function (e) {
            if ((e.which && e.which == 13) || (e.keyCode && e.keyCode == 13)) {
                $(this).blur();
                if (is1751) {
                    $(e.target).blur();
                }
                $('#btnSubmit').eq(0).click();
                return false;
            }
        });
    }
}

function ValidateFormStep1($optionalExcludedElems) {
    var $excludedElems = $optionalExcludedElems || $('input.ignore:text[value=""], select.ignore, textarea, #bkg_divRewards input, #divPayment .ignore');
    return $('input[type=text]:visible, select:visible').not($excludedElems).valid();
}