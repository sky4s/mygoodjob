
//build popup on page load
$(document).ready(function () {
    $("a.modalpopup").attr("disabled", true);
    $('a.modalpopup, area.modalpopup, input.modalpopup').click(function (e) {
        e.preventDefault();
        this.blur();
        Agoda_initialPopup(this);
        return false;
    });
    $("a.modalpopup").attr("disabled", false);
});

function Agoda_initialPopup(domClass) {
    var queryString = domClass.getAttribute('data-href') || domClass.href || domClass.alt;
    queryString = queryString.replace(/^[^\?]+\??/, '');
    var params = parseQueryPopup(queryString);

    if (typeof mp_closeTxt == 'undefined') {
        mp_closeTxt = domClass.getAttribute("closeText")
    }

    if (typeof mp_loadingText == 'undefined') {
        mp_loadingText = "Loading...";
    }

    var popupName = domClass.getAttribute('popupName') || '';

    eval("option" + popupName + " = {"
            + "popupName: '" + popupName + "' || '',"
            + "titleText: domClass.getAttribute('data-popup-title') || domClass.getAttribute('popupTitle') || mp['titleText'] || domClass.title || domClass.name || null,"
            + "contentUrl: domClass.href || domClass.alt || '#',"
            + "closeText: domClass.getAttribute('data-popup-closetext') || domClass.getAttribute('closeText') || mp_closeTxt ||  mp['closeText']  || 'Close',"
            + "loadingImage: domClass.getAttribute('loadingImage') || 'https://img.agoda.net/images/default/preload.gif',"
            + "loadingText: domClass.getAttribute('loadingText') || params['loadingtext'] || mp_loadingText,"
            + "popupWidth: domClass.getAttribute('data-popup-width') || domClass.getAttribute('popupWidth') || params['width'] || domClass.width || 630,"
            + "popupHeight: domClass.getAttribute('data-popup-height') || domClass.getAttribute('popupHeight') || params['height'] || domClass.height || 440,"
            + "popupSize: domClass.getAttribute('PopupSize') || params['PopupSize'] || '',"
            + "minWidth: 630,"
            + "minHeight: 440,"
            + "useScale: false,"
            + "popupScale: 80,"
            + "showLoadingPopup: domClass.getAttribute('showLoading') == 'false' ? false : true || true,"
            + "LoadingPosition: domClass.getAttribute('loadingPosition') || 'out',"
            + "popupFreeze: domClass.getAttribute('popupFreeze') == 'true' ? true : false || false,"
            + "noBorder: params['noborder'] == 1 ? true : false || false,"
            + "footerText: domClass.getAttribute('footerText') || '',"
            + "idModalPopup: 'MP_window" + popupName + "',"
            + "idIFrameContent: 'MP_iframeContent" + popupName + "',"
            + "idOverlay: 'MP_overlay" + popupName + "',"
            + "idLoad: 'MP_loading" + popupName + "',"
            + "idCloseButton: 'MP_closeButton" + popupName + "',"
            + "idHideSelect: 'MP_HideSelect" + popupName + "',"
            + "idParentFrame: domClass.getAttribute('parentName') || ''"
            + "}");

    eval("if (option" + popupName + ".popupSize.length > 0) {"
            + "option" + popupName + ".useScale = true;"
            + "option" + popupName + ".popupScale = option" + popupName + ".popupSize;"
            + "option" + popupName + ".showLoadingPopup = true;"
             + "option" + popupName + ".LoadingPosition = 'in';"
            + "option" + popupName + ".minWidth = 785;"
            + "option" + popupName + ".minHeight = 525;"
            + "} else {"
            + "option" + popupName + ".useScale = false;"
            + "}");

    //Show popup   
    eval("Agoda_showPopup('" + popupName + "');");
    eval("var useScale = option" + popupName + ".useScale;");

    if (useScale) {
        $(window).resize(function () {
            if (this.resizeTO) clearTimeout(this.resizeTO);
            this.resizeTO = setTimeout(function () {
                $(this).trigger('resizeEnd');
            }, 200);
        });

        $(window).bind('resizeEnd', function () {
            if (document.getElementById(option.idIFrameContent)) {
                eval("option" + popupName + ".contentUrl = document.getElementById(option.idIFrameContent).contentWindow.location.href;");
            }
            //Reload popup
            eval("Agoda_showPopup('" + popupName + "');");
        });
    }
}

function Agoda_showPopup(popupName) {
    eval("var _option = option" + popupName + ";");

    var popupWidth = _option.popupWidth;
    var popupHeight = _option.popupHeight;

    if (_option.useScale) {
        //Resizable popup
        popupWidth = ($(window).width() * _option.popupScale) / 100;
        popupHeight = ($(window).height() * _option.popupScale) / 100;

        if (popupWidth < _option.minWidth) { popupWidth = _option.minWidth; }
        if (popupHeight < _option.minHeight) { popupHeight = _option.minHeight; }

        if (popupWidth != _option.popupWidth || popupHeight != _option.popupHeight) {
            _option.popupWidth = popupWidth;
            _option.popupHeight = popupHeight;
        }
    }
    else {
        //Fixed size popup
        _option.popupWidth = popupWidth;
        _option.popupHeight = popupHeight;
    }

    //Save current width and height
    eval("option" + popupName + ".popupWidth = popupWidth;");
    eval("option" + popupName + ".popupHeight = popupHeight;");

    //Remove existing tag
    if ($("#" + _option.idOverlay).length > 0) { $("#" + _option.idOverlay).remove(); }
    if ($("#" + _option.idLoad).length > 0) { $("#" + _option.idLoad).remove(); }
    if ($("#" + _option.idModalPopup).length > 0) { $("#" + _option.idModalPopup).remove(); }

    //Add popup tags
    var iframeWidth = popupWidth - 24;
    var iframeHeight = popupHeight - 30;

    $("body").append(Agoda_buildPopupContent(popupName, iframeWidth, iframeHeight));

    $("#" + _option.idOverlay).css({ opacity: 0.35 });

    $("#" + _option.idModalPopup).css({ marginLeft: '-' + parseInt((popupWidth / 2), 10) + 'px', width: popupWidth + 'px' });

    //fix exit popup before iframe loaded
    if (_option.idParentFrame!="") {
        var doc = document.getElementById(_option.idParentFrame).contentWindow.document;
        if (doc.attachEvent) {
            //for IE
            doc.attachEvent("onkeyup", function (e) {
                var keycode = (e.keyChar) ? e.keyChar : ((e.keyCode) ? e.keyCode : e.which);
                if (keycode == 27) { // close   
                    eval("Agoda_closePopup('" + popupName + "');");
                    return false;
                }
                
            });
        }
        else {
            doc.addEventListener("keyup", function (e) {
                var keycode = (e.keyChar) ? e.keyChar : ((e.keyCode) ? e.keyCode : e.which);
                if (keycode == 27) { // close
                    eval("Agoda_closePopup('" + popupName + "');");
                    return false;
                }
            }, false);
        }
    }

    if (!(jQuery.browser.msie && jQuery.browser.version < 7)) { // take away IE6
        $("#" + _option.idModalPopup).css({ marginTop: '-' + parseInt((popupHeight / 2), 10) + 'px' });
    }

    if (_option.showLoadingPopup == true && _option.LoadingPosition == 'out') {
        $("#" + _option.idLoad).show();
        $("#" + _option.idModalPopup).css("display", "none");
    }
    else if (_option.showLoadingPopup == false) {
        $("#" + _option.idLoad).hide();
        $("#" + _option.idModalPopup).css("display", "block");
    } else {
        $("#" + _option.idLoad).show();
        $("#" + _option.idModalPopup).css("display", "block");
    }

    //Add popup events
    if (_option.popupFreeze == false) {
        $("#" + _option.idOverlay).click(function () {
            eval("Agoda_closePopup('" + popupName + "');");
            return false;
        });
        $("#" + _option.idCloseButton).click(function () {
            eval("Agoda_closePopup('" + popupName + "');");
            return false;
        });    

        //Add keyboard event
        document.onkeyup = function (e) {
            if (e == null) { // ie
                keycode = event.keyCode;
            } else { // mozilla
                keycode = e.which;
            }
            if (keycode == 27) { // close
                eval("Agoda_closePopup('" + popupName + "');");
                return false;
            }
        };
    }

    $('iframe#' + _option.idIFrameContent).load(function () {
        if (_option.popupFreeze == false) {
            var doc = document.getElementById(_option.idIFrameContent).contentWindow.document;
            if (doc.attachEvent) {
                //for IE
                doc.attachEvent("onkeyup", function (e) {
                    var keycode = (e.keyChar) ? e.keyChar : ((e.keyCode) ? e.keyCode : e.which);
                    if (keycode == 27) { // close
                        eval("Agoda_closePopup('" + popupName + "');");
                        return false;
                    }
                });
            }
            else {
                doc.addEventListener("keyup", function (e) {
                    var keycode = (e.keyChar) ? e.keyChar : ((e.keyCode) ? e.keyCode : e.which);
                    if (keycode == 27) { // close
                        eval("Agoda_closePopup('" + popupName + "');");
                        return false;
                    }
                }, false);
            }

            $("#" + _option.idLoad).hide();
        }

        $("#" + _option.idModalPopup).css("display", "block");
        $("#" + _option.idIFrameContent).css("display", "block");
        $('iframe#' + _option.idIFrameContent).focus();
    });
}

function Agoda_closePopup(popupName) {
    eval("var _option = option" + popupName + ";");

    $("#" + _option.idOverlay).unbind("click");
    $("#" + _option.idCloseButton).unbind("click");
    $("#" + _option.idModalPopup).fadeOut("fast", function () { $('#' + _option.idModalPopup + ',#' + _option.idOverlay + ",#" + _option.idHideSelect).trigger("unload").unbind().remove();});

    $("#" + _option.idLoad).remove();

    if (this.resizeTO) this.resizeTO = null;
    $(window).unbind('resizeEnd');
    $(window).resize = "";

    document.onkeyup = "";

    if (_option.idParentFrame != '') {
        if (jQuery.browser.msie) {
            if ($('iframe#' + _option.idParentFrame) != null) {
                if ($('iframe#' + _option.idParentFrame).get(0).contentWindow!=null)
                    $('iframe#' + _option.idParentFrame).get(0).contentWindow.focus();
            }

        } else {
            $('iframe#' + _option.idParentFrame).focus();
        }
    }
}

function Agoda_buildPopupContent(popupName, iframeWidth, iframeHeight) {
    eval("var _option = option" + popupName + ";");

    //Add popup tags
    if (_option.useScale) {
        iframeHeight = iframeHeight - 80;
    }
    var content = "";

    if (typeof document.body.style.maxHeight === "undefined") {//if IE 6
        if (document.getElementById(_option.idHideSelect) === null) {//iframe to hide select elements in ie6
            content += "<iframe id='" + _option.idHideSelect + "' class='mpopup_hideselect'></iframe>";
        }
    }

    content += "<div id='" + _option.idOverlay + "' class='mpopup_overlay'></div>";

    if (_option.showLoadingPopup == true) {
        if (_option.LoadingPosition == 'in') {
            content += "<div id='" + _option.idModalPopup + "' class='mpopup_window'>";
            content += "<div id='" + _option.idLoad + "' class='mpopup_loading loading_nobd'><img src='" + _option.loadingImage + "' /><span>" + _option.loadingText + "</span></div>";
        } else {
            content += "<div id='" + _option.idLoad + "' class='mpopup_loading'><img src='" + _option.loadingImage + "' /><span>" + _option.loadingText + "</span></div>";
            content += "<div id='" + _option.idModalPopup + "' class='mpopup_window'>";
        }
    }
    else {
        content += "<div id='" + _option.idModalPopup + "' class='mpopup_window'>";
        content += "<div id='" + _option.idLoad + "' class='mpopup_loading loading_nobd'><img src='" + _option.loadingImage + "' /><span>" + _option.loadingText + "</span></div>";
    }

    var removeBorderStr = "";
    if (_option.noBorder == true) {
        removeBorderStr = " border: 0; margin:0 12px 10px";
    }

    content += "<div id='MP_header" + popupName + "' class='mpopup_header'>";
    content += "<table cellspacing='0' cellpadding='0' class='widthfull'>";
    content += "<tr>";
    content += "<td><div id='MP_titleDiv" + popupName + "' class='mpopup_title'><div id='MP_titleText" + popupName + "' class='fontmediumb'>" + _option.titleText + "</div></div></td>";

    if (_option.popupFreeze == false) {
        content += "<td><div id='MP_closeDiv" + popupName + "' class='mpopup_btnclose'><a href='#' id='" + _option.idCloseButton + "'>" + _option.closeText + "<span class='sprite mp-btn-close'></span></a></div></td>";
    }

    content += "</table>";
    content += "</div>";
    content += "<div id='MP_divFrame" + popupName + "' class='mpopup_diviframe' style='" + removeBorderStr + "'><iframe frameborder='0' hspace='0' class='iframeClass' src='" + _option.contentUrl + "' id='" + _option.idIFrameContent + "' name='" + _option.idIFrameContent + "' style='width:" + iframeWidth + "px;height:" + iframeHeight + "px;' scrolling='no'></iframe></div>";

    if (_option.footerText != "") {
        content += "<div id='MP_footer" + popupName + "' class='mpopup_footer'>";
        content += "<table cellspacing='0' cellpadding='0' class='widthfull'>";
        content += "<tr>";
        content += "<td><div id='MP_FooterDiv" + popupName + "'><div id='MP_footerText" + popupName + "' class='fontsmallb tex_left'>" + _option.footerText + "</div></div></td>";
        content += "</table>";
        content += "</div>";
    }

    content += "</div>";

    return content;
}

function parseQueryPopup(query) {
    var Params = {};
    if (!query) { return Params; } // return empty object
    var Pairs = query.split(/[;&]/);
    for (var i = 0; i < Pairs.length; i++) {
        var KeyVal = Pairs[i].split('=');
        if (!KeyVal || KeyVal.length != 2) { continue; }
        var key = unescape(KeyVal[0]);
        var val = unescape(KeyVal[1]);
        val = val.replace(/\+/g, ' ');
        Params[key] = val;
    }
    return Params;
}




