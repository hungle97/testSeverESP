
window.onload = updateA0();
function updateA0(){
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function (){
        if( this.readyState == 4 && this.status == 200){
            document.getElementById('val').style.width = (parseFloat(xhttp.responseText)/10.24).toFixed(2)+'%';
            document.getElementById('val').innerHTML = (parseFloat(xhttp.responseText)/10.24).toFixed(2)+'%';
            updateA0();
        }
    }
    xhttp.open('GET','/a0.html',true);
    xhttp.send();
}
function bat() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET','/bat.html',true);
    xhttp.send();
}
function tat() {
    var xhttp = new XMLHttpRequest();
    xhttp.open('GET','/tat.html',true);
    xhttp.send();
}
