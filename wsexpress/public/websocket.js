/*
file if you want to seperate the javacript from HTML
*/

var host = "192.168.1.3";
var ws = new WebSocket('ws://' + host + ':8080');

//ws.send()
//ws.addEventListener('message', function(event){});

function init(){
  ws.addEventListener('message', function(event){
    //event.data == message string
    var message = document.getElementById('messages').innerHTML = event.data;
  });
}


window.addEventListener('load', init);
