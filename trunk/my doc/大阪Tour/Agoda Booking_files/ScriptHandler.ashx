
if (typeof is1372 === 'undefined') {
    var is1372 = false;
}

if (typeof rndccy === 'undefined') {
    var rndccy = "BIF,BYR,DJF,GNF,JPY,KMF,KRW,PYG,RWF,VND,VUV,XPF,IDR,TWD,HUF";
}

var counter1372 = {};
var start1372 = {};

var executetime = {};
//var _timeout = 15000; // ** where should we get from web.config or afm_configurations?
if (typeof _timeout === 'undefined') {
    var _timeout = 15000;
}

function SendAjax(urlMethod, jsonData, returnFunction, methodname) {

    var name = "";
    var isbooked = false;
    if (typeof methodname === 'undefined' || methodname == '') {
        var strs = urlMethod.split("/");
        var rdmnumber = Math.floor(Math.random() * 1001);

        if (strs.length > 3) {
            var names = strs[3].split("?");
            if (names.length > 0) {
                name = names[0] + "|" + rdmnumber;
               
                if (names[0].toLowerCase() == "dobook") {                    
                    isbooked = true;
                }
            }
        }
    } else {
        name = methodname;
    }

    if (is1372 && !isbooked) {
        $.ajax({
            type: "POST",
            contentType: "application/json; charset=utf-8",
            url: urlMethod + '&nocache=' + new Date().getTime(),
            data: jsonData,
            dataType: "json",
            timeout: _timeout,
            beforeSend: function (jqXHR, settings) {
                start1372[name] = 0;
                start1372[name] = new Date().getTime();
            },
            success: function (msg) {
                // Do something interesting here.
                if (msg != null && typeof returnFunction !== 'undefined') {
                    returnFunction(msg);
                }
            },
            error: function (xhr, status, error) {
                // Boil the ASP.NET AJAX error down to JSON.
                var err = eval("(" + xhr.responseText + ")");

                // Display the specific error raised by the server
                //alert(err.Message);
                // Session Expire
                disabledConfirm_exit = true;
                if (typeof err !== 'undefined' && err.Message == "The session has expired.") {
                    window.location = timeoutexceptionPage;
                }
                else {
                    window.location = exceptionPage;
                }
            },
            complete: function (jqXHR, textStatus) {
                //the textStatus of the request ("success", "notmodified", "error", "timeout", "abort", or "parsererror").             

                if (isNaN(counter1372[name])) {
                    counter1372[name] = 0;
                }

                counter1372[name]++;

                if (textStatus == "success") {
                    counter1372[name] = 1;
                } else {

                    executetime[name] = 0;
                    executetime[name] = (new Date().getTime()) - start1372[name];

                    var strname = name.split("|");
                    if (strname.length <= 0) {
                        return;
                    }

                    $.post('/b/ClientTechnoStatLog.aspx?data=' + strname[0] + '|' + executetime[name] + '|' + counter1372[name] + ', status: ' + textStatus);

                    if (counter1372[name] > 3) {
                        disabledConfirm_exit = true;
                        window.location = exceptionPage;
                    } else if (counter1372[name] == 3) {
                        disabledConfirm_exit = true;
                        location.reload();
                    } else {
                        //load again                               
                        SendAjax(urlMethod, jsonData, returnFunction, name);
                    }
                }
            }
        });
    } else {
        $.ajax({
            type: "POST",
            contentType: "application/json; charset=utf-8",
            url: urlMethod + '&nocache=' + new Date().getTime(),
            data: jsonData,
            dataType: "json",
            success: function (msg) {
                // Do something interesting here.
                if (msg != null && typeof returnFunction !== 'undefined') {
                    returnFunction(msg);
                }
            },
            error: function (xhr, status, error) {
                // Boil the ASP.NET AJAX error down to JSON.
                var err = eval("(" + xhr.responseText + ")");

                // Display the specific error raised by the server
                //alert(err.Message);
                // Session Expire
                disabledConfirm_exit = true;
                if (typeof err !== 'undefined' && err.Message == "The session has expired.") {
                    window.location = timeoutexceptionPage;
                }
                else {
                    window.location = exceptionPage;
                }
            }
        });
    }
}

function SendAjaxV2(urlMethod, jsonData, returnFunction, afterFinishFunction) {

    $.when($.ajax({
        type: "POST",
        contentType: "application/json; charset=utf-8",
        url: urlMethod,
        data: jsonData,
        dataType: "json",
        success: function (msg) {
            // Do something interesting here.
            if (msg != null) {
                returnFunction(msg);
            }
        },
        error: function (xhr, status, error) {
            // Boil the ASP.NET AJAX error down to JSON.
            var err = eval("(" + xhr.responseText + ")");
            //alert(err.Message);
            // Session Expire
            disabledConfirm_exit = true;
            if (typeof err !== 'undefined' && err.Message == "The session has expired.") {
                window.location = timeoutexceptionPage;
            }
            else {
                window.location = exceptionPage;
            }
        }
    })).then(afterFinishFunction);

}

function SendAjaxSync(urlMethod, jsonData, returnFunction) {

    var name = "";
    var strs = urlMethod.split("/");
    var rdmnumber = Math.floor(Math.random() * 1001);

    if (strs.length > 3) {
        var names = strs[3].split("?");
        if (names.length > 0) {
            name = names[0] + "|" + rdmnumber;
        }
    }

    if (is1372) {
        $.ajax({
            type: "POST",
            headers: { "cache-control": "no-cache" },
            contentType: "application/json; charset=utf-8",
            async: false,
            url: urlMethod + '&nocache=' + new Date().getTime(),
            data: jsonData,
            dataType: "json",
            timeout: _timeout,
            beforeSend: function (jqXHR, settings) {

                start1372[name] = 0;
                start1372[name] = new Date().getTime();

            },
            success: function (msg) {
                // Do something interesting here.
                if (msg != null) {
                    returnFunction(msg);
                }
            },
            error: function (xhr, status, error) {
                // Boil the ASP.NET AJAX error down to JSON.
                var err = eval("(" + xhr.responseText + ")");
                //alert(err.Message);
                // Session Expire
                disabledConfirm_exit = true;
                if (typeof err !== 'undefined' && err.Message == "The session has expired.") {
                    window.location = timeoutexceptionPage;
                }
                else {
                    window.location = exceptionPage;
                }
            },
            complete: function (jqXHR, textStatus) {

                if (isNaN(counter1372[name])) {
                    counter1372[name] = 0;
                }

                counter1372[name]++;

                if (textStatus == "success") {
                    counter1372[name] = 1;
                } else {

                    executetime[name] = 0;
                    executetime[name] = (new Date().getTime()) - start1372[name];

                    var strname = name.split("|");
                    if (strname.length <= 0) {
                        return;
                    }

                    $.post('/b/ClientTechnoStatLog.aspx?data=' + strname[0] + '|' + executetime[name] + '|' + counter1372[name] + ', status: ' + textStatus);

                    if (counter1372[name] > 3) {
                        disabledConfirm_exit = true;
                        window.location = exceptionPage;
                    } else if (counter1372[name] == 3) {
                        disabledConfirm_exit = true;
                        location.reload();
                    } else {
                        //load again                               
                        SendAjaxSync(urlMethod, jsonData, returnFunction);
                    }
                }
            }
        });
    } else {
        $.ajax({
            type: "POST",
            headers: { "cache-control": "no-cache" },
            contentType: "application/json; charset=utf-8",
            async: false,
            url: urlMethod + '&nocache=' + new Date().getTime(),
            data: jsonData,
            dataType: "json",
            success: function (msg) {
                // Do something interesting here.
                if (msg != null) {
                    returnFunction(msg);
                }
            },
            error: function (xhr, status, error) {
                // Boil the ASP.NET AJAX error down to JSON.
                var err = eval("(" + xhr.responseText + ")");
                //alert(err.Message);
                // Session Expire
                disabledConfirm_exit = true;
                if (typeof err !== 'undefined' && err.Message == "The session has expired.") {
                    window.location = timeoutexceptionPage;
                }
                else {
                    window.location = exceptionPage;
                }
            }
        });
    }

}

function CheckNumeric(e) {
    var regNum = new RegExp("^[0-9]+$", "g");
    var regNotNum = new RegExp("[^0-9]+", "g");
    if (e.target.value != "") {
        if (e.target.value.match(regNum) == null) {
            e.target.value = e.target.value.replace(regNotNum, "");
            e.target.focus();
            return;
        }
    }
}

function getkeycode(e) {
    var keynum;

    if (!e) var e = window.event;

    if (e.keyCode) keynum = e.keyCode;
    else if (e.which) keynum = e.which;
    return keynum;
}

function CheckNumeric2(e) {

    var keynum = getkeycode(e);

    if (keynum == 8 || keynum == 9 || keynum == 35 || keynum == 36 || keynum == 37 || keynum == 39 || keynum == 46 || keynum == 16)
        return true;

    if (keynum < 48 || keynum > 57) {
        e.preventDefault ? e.preventDefault() : e.returnValue = false;
    } else {
        return true;
    }
}

function ValidateGeneralInput(e) {
    var key = e.charCode || e.keyCode || 0;
    var reg_allow = new RegExp("^[a-zA-Z0-9_ \"\\[\\]\\{\\}!&\\-:@+*\\\\/\\(\\)\\?,.=$|\r\n]+$", "g");
    var reg_delete = new RegExp("[^a-zA-Z0-9_ \"\\[\\]\\{\\}!&\\-:@+*\\\\/\\(\\)\\?,.=$|\r\n]+", "g");
    if (key != 46 && key != 8) {
        if (e.target.value != "") {
            if (e.target.value.match(reg_allow) == null) {
                alert(errorEnglish);
                e.target.value = e.target.value.replace(reg_delete, "");
                e.target.focus();
                return;
            }
        }
    }
}

//function ValidateNameDotInput(e) {
//    var key = e.charCode || e.keyCode || 0;
//    reg_allow = new RegExp("^[a-zA-Z-. ]+$", "g");
//    reg_delete = new RegExp("[^a-zA-Z-. ]+", "g");
//    if (key != 46 && key != 8) {
//        if (e.target.value != "") {
//            if (e.target.value.match(reg_allow) == null) {
//                alert(errorEnglish);
//                e.target.value = e.target.value.replace(reg_delete, "");
//                e.target.focus();
//                return;
//            }
//        }
//    }
//}

function ValidateNameInput(e) {
    var key = e.charCode || e.keyCode || 0;
    reg_allow = new RegExp("^[a-zA-Z-. ]+$", "g");
    reg_delete = new RegExp("[^a-zA-Z-. ]+", "g");
    if (key != 46 && key != 8) {
        if (e.target.value != "") {
            if (e.target.value.match(reg_allow) == null) {
                alert(errorEnglish);
                e.target.value = e.target.value.replace(reg_delete, "");
                e.target.focus();
                return;
            }
        }
    }
}

function CardNumberKeyPress(e) {
    var key = e.charCode || e.keyCode || 0;
    // allow backspace, tab, delete, arrows, numbers and keypad numbers ONLY
    return (
                key == 8 ||
                key == 9 ||
                key == 46 ||
                (key >= 37 && key <= 40) ||
                (key >= 48 && key <= 57) ||
                (key >= 96 && key <= 105));

}


function ismaxlength(obj, mlength) {
    if (obj && obj.value.length > mlength)
        obj.value = obj.value.substring(0, mlength)
}


function showContent(div) {
    var d = document.getElementById(div);
    if (d) {
        d.style.display = 'block';
    }
}

function hideContent(div) {
    var d = document.getElementById(div);
    if (d) {
        d.style.display = 'none';
    }
}

function unescapeString(txt) {
    var result = txt;
    result = result.replace(/&#8217;/g, "'");
    return result;
}

function getUrlMethod(page, methodName) {
    return "/b/" + page + "/" + methodName + "?p=" + p;
}

function ValidCCExpireDate_ClientValidatePaymentForm(sender, args) {

    var cardtype = document.getElementById("ddlCreditCardAB").value;
    var checkoutDate = document.getElementById("hiddenCheckoutDate").value;
    var expmonth = document.getElementById("ddlExpMonth").value;
    var expyear = document.getElementById("ddlExpYear").value;
    var month = expmonth;
    var year = expyear;

    if (month != 0 && year != 0) {
        var d = new Date();
        var curr_date = d.getDate();
        var curr_month = d.getMonth();
        var curr_year = d.getFullYear();
        var iexpyear = year;
        var iexpmonth = month;
        var icheckoutyear = parseInt(curr_year);
        var icheckoutmonth = parseInt(curr_month);

        if (iexpyear == icheckoutyear) {
            if (iexpmonth >= icheckoutmonth + 1) {
                args.IsValid = true;
            } else {
                args.IsValid = false;
            }
        }
        else if (iexpyear < icheckoutyear) {
            args.IsValid = false;
        } else {
            args.IsValid = true;
        }
    }
}

function custEnsureFilled_ClientValidatePaymentForm(sender, args) {

    var cardtype = document.getElementById("ddlCreditCardAB").value;

    var cardnumber = document.getElementById("txtCardNoAB").value;
    var holdername = document.getElementById("txtHolderAB").value;
    var expmonth = document.getElementById("ddlExpMonth").value;
    var expyear = document.getElementById("ddlExpYear").value;
    var cvccode = ''
    if (document.getElementById("txtCVCCodeAB")) {
        cvccode = document.getElementById("txtCVCCodeAB").value;
    }

    var isAmex = 4;

    cardnumber = $.trim(cardnumber);
    holdername = $.trim(holdername);
    cvccode = $.trim(cvccode);

    if (cardtype == 0 || cardnumber == '' || holdername == '' || expmonth == 0 || expyear == 0 || cvccode == '') {
        args.IsValid = false;
        $find('mdlPopup').hide();

        if (cardtype == 0) {
            document.getElementById("ddlCreditCardAB").focus();
        } else if (cardnumber == '') {
            document.getElementById("txtCardNoAB").focus();
        } else if (holdername == '') {
            document.getElementById("txtHolderAB").focus();
        } else if (expmonth == 0) {
            document.getElementById("ddlExpMonth").focus();
        } else if (expyear == 0) {
            document.getElementById("ddlExpYear").focus();
        } else if (cvccode == '') {
            document.getElementById("txtCVCCodeAB").focus();
        }
    } else {
        if (cardtype != isAmex) {
            // visa, master, jcb need to check billing address fields
            var issuingbank = ''
            var country = 0

            if (document.getElementById("txtIssuingBankAB") != null)
                issuingbank = document.getElementById("txtIssuingBankAB").value;

            if (document.getElementById("ddlCountryAB") != null)
                country = document.getElementById("ddlCountryAB").value;

            issuingbank = $.trim(issuingbank);

            if (issuingbank == '' || country == 0) {

                args.IsValid = false;
                $find('mdlPopup').hide();

                if (country == 0) {
                    document.getElementById("ddlCountryAB").focus();
                } else if (issuingbank == '') {
                    document.getElementById("txtIssuingBankAB").focus();
                }
            } else {
                args.IsValid = true;
            }

        } else {
            if (cardtype == isAmex) {
                // Amex need to check country field
                var country = 0
                country = document.getElementById("ddlCountryAB").value;

                if (country == 0) {
                    document.getElementById("ddlCountryAB").focus();
                    $find('mdlPopup').hide();
                    args.IsValid = false;
                } else { args.IsValid = true; }
            } else { args.IsValid = true; }
        }
    } //if focus
}

function ShowWaitingPopup() {

    $find('mdlPopup').show();

    if (typeof amendID === 'undefined') {
        var amendID = 0;
    }

    var cardtype = 0;
    var cardnumber = '';
    var cvccode = '';

    var txtcvc;
    var txtcardno;

    if (amendID > 0) {
        if (document.getElementById("ddlCreditCardAB") != null)
            cardtype = document.getElementById("ddlCreditCardAB").value;

        if (document.getElementById("txtCardNoAB") != null) {
            txtcardno = document.getElementById("txtCardNoAB");
            cardnumber = txtcardno.value;
        }

        if (document.getElementById("txtCVCCodeAB") != null) {
            txtcvc = document.getElementById("txtCVCCodeAB");
            cvccode = txtcvc.value;
        }

    } else {

        if (document.getElementById("ddlCreditCard") != null)
            cardtype = document.getElementById("ddlCreditCard").value;

        if (document.getElementById("txtCardNo") != null) {
            txtcardno = document.getElementById("txtCardNo");
            cardnumber = txtcardno.value;
        }

        if (document.getElementById("txtCVCCode") != null) {
            txtcvc = document.getElementById("txtCVCCode");
            cvccode = txtcvc.value;
        }
    }

    var isAmex = 4;

    if (cardtype == isAmex) {
        if ($.trim(cvccode) == '' || cvccode.length != 4) {
            if (txtcvc != null)
                txtcvc.focus();

            $find('mdlPopup').hide();
        }

        if ($.trim(cardnumber) == '' || cardnumber.length != 15) {
            if (txtcardno != null)
                txtcardno.focus();

            $find('mdlPopup').hide();
        }
    }
    else {
        if ($.trim(cvccode) == '' || cvccode.length != 3) {
            if (txtcvc != null)
                txtcvc.focus();

            $find('mdlPopup').hide();
        }
        if ($.trim(cardnumber) == '' || cardnumber.length != 16) {
            if (txtcardno != null)
                txtcardno.focus();

            $find('mdlPopup').hide();
        }
    }

    var regNum = new RegExp("^[0-9]+$", "g");
    if (cardnumber.match(regNum) == null) {
        if (txtcardno != null)
            txtcardno.focus();

        $find('mdlPopup').hide();
    }

    if (cvccode.match(regNum) == null) {
        if (txtcvc != null)
            txtcvc.focus();

        $find('mdlPopup').hide();
    }

    // } // catch
}

function AddCommas(nStr) {
    nStr += '';
    x = nStr.split('.');
    x1 = x[0];
    x2 = x.length > 1 ? '.' + x[1] : '';
    var rgx = /(\d+)(\d{3})/;
    while (rgx.test(x1)) {
        x1 = x1.replace(rgx, '$1' + ',' + '$2');
    }
    return x1 + x2;
}

function IsDecimalPoint(currency) {

    return rndccy.indexOf(currency) == -1;
}
function isiPad() { 
    return (navigator.userAgent.match(/iPad/i) != null); 
} 
function isiPhone() { 
    return ((navigator.platform.indexOf("iPhone") != -1) || (navigator.platform.indexOf("iPod") != -1));
} 
function isiPadPortrait() { 
    return (isiPad() && (Math.abs(window.orientation) == 0));
}
function isTouchDevice() {
    return !!('ontouchstart' in window) // works on most browsers 
        || !!('onmsgesturechange' in window); // works on ie10
};

var BookingForm = BookingForm || {};
BookingForm.Utils = BookingForm.Utils || {};

BookingForm.Utils.technoMessage = function (technoID, elapsedTime, data) {
    $.ajax({
        url: '/b/handlers/MessageSenderHandler.ashx',
        data: { msgType: 'technoMessage', msgID: technoID, elapsedTime: elapsedTime, data: data }
    });
}