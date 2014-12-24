
//
//(function ($) {
//    $.post( "http://localhost:8081/chairresults/user/contest-status", function( data ) {
//        if(data == '1') {
//            $("a#show-contest").trigger("click");
//        //            $.colorbox({width:"30%", inline:true, href:"#contest-popup"});
//        }
//    });
// 
//})(jQuery);

function disassociate_from_hcf(){
    {
        var x = confirm("Are you sure you want to disassociate from HCF?. All of your content will be unpublished untill associated with new HCF.");
        if (x)
            return true;
        else
            return false;
    }
}

function disassociate_hcp(){
    {
        var x = confirm("Are you sure you want to disassociate HCP?. All content published by you will be removed from HCF page.");
        if (x)
            return true;
        else
            return false;
    }
}

function openWindow(location){
    if(location == "#")return;
    window.open(location,'_self');
}
function toggle_visibility()
{
    var e = document.getElementById("views-exposed-form-hairstyle-search-results-page");
    if(e.style.display == 'block'){
        e.style.display = 'none';
        document.getElementById("show_hide").innerHTML = "Show Filters"; 
    }
    else
    {
        e.style.display = 'block';
        document.getElementById("show_hide").innerHTML = "Hide Filters"; 
  
    }
}
function toggle_visibility_deal()
{
    var e = document.getElementById("views-exposed-form-deal-search-page");
    if(e.style.display == 'block'){
        e.style.display = 'none';
        document.getElementById("show_hide1").innerHTML = "Show Filters";
    }
    else
    {
        e.style.display = 'block';
        document.getElementById("show_hide1").innerHTML = "Hide Filters";
    }
}
function toggle_visibility_hcf()
{
    var e = document.getElementById("views-exposed-form-hcf-search-results-page");
    if(e.style.display == 'block'){
        e.style.display = 'none';
        document.getElementById("show_hide2").innerHTML = "Show Filters";
    }
    else
    {
        e.style.display = 'block';
        document.getElementById("show_hide2").innerHTML = "Hide Filters";
    }
}
function toggle_visibility_sr()
{
    var e = document.getElementById("views-exposed-form-service-request-results-page");
    if(e.style.display == 'block')
    {
        e.style.display = 'none';
        document.getElementById("show_hide3").innerHTML = "Show Filters";
    }
    else
    {
        e.style.display = 'block';
        document.getElementById("show_hide3").innerHTML = "Hide Filters";
    }
}
    
    


window.alert = function(arg) { if (window.console && console.log) { console.log(arg);}};
(function ($) {
$(document).ready(function(){
}); // END document ready
})(jQuery);