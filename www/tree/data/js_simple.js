var ie = document.all;
var ns = document.getElementById && !ie;

document.getElementById('tree').onclick=function(e)
{
    var e = ns ? e : event;
    var obj = ns ? e.target : event.srcElement;

    if (obj.tagName == "P" && obj.nextSibling.tagName == "DIV") {
        var div = obj.nextSibling;
        if (div.style.display != "block") {
            div.style.display = "block";
            obj.setAttribute("class", "close");
            obj.setAttribute("className", "close");
        }
        else {
            div.style.display = "none";
            obj.setAttribute("class", "open");
            obj.setAttribute("className", "open");
        }
    }
}

/*
window.addEvent('domready', function() {
    var current;

    var tree = document.getElementById("tree");
    var p = tree.getElementsByTagName("p");

    /*
    for (var i = 0; i < p.length; i++) {
        var link = p[i];
        var div = link.nextSibling;

        if (div && div.tagName == "DIV") {
            div.slide = new Fx.Slide(div);
            div.slide.hide();

            div.slide.addEvent('complete', function() {
                p = current.parentNode.previousSibling;
                if (current.parentNode.style.height != "" && current.parentNode.style.height != "0px") {
                    current.parentNode.style.height = "auto";
                    p.setAttribute("class", "close");
                    p.setAttribute("className", "close");
                }
                else {
                    p.setAttribute("class", "open");
                    p.setAttribute("className", "open");
                }
            });
        }
    }

    $('tree').addEvent('click', function(e){
        alert(e.target.tagName);
                       /*
        if (e.target.tagName == "P") {
            current = e.target.nextSibling.firstChild;
            current.slide.toggle();
            e.stop();
        }
    });
});
*/
