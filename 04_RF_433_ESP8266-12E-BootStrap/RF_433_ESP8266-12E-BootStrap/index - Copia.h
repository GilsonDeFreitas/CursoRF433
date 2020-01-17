const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-br">
<head>
<meta charset = "utf-8">
<style>
.card{
    max-width: 400px;
     min-height: 250px;
     background: #02b870;
     padding: 30px;
     box-sizing: border-box;
     color: #FFF;
     margin:20px;
     box-shadow: 0px 2px 18px -4px rgba(0,0,0,0.75);
}
</style>
</head>
<body>

<div class="card">
  <h1>TEMPERATURA</h1><br>
  <h2>Graus: <span id="ADCValue">0</span> C</h2><br>
  <h2>Feito por Gilson de Freitas para teste Evaldo</h2><br>
  //<br><a href="http://curseagora.com.br/">CurseAgora.com</a>
</div>

<div class="card">
  <h1>LED 01</h1><br>
  <h2>Status <span id="Variavel01">0</span> </h2><br>
  <h2>On-Off</h2><br>
</div>

<div class="card">
  <h1>LED 02</h1><br>
  <h2>Status <span id="Variavel02">0</span></h2><br>
  <h2>On-Off</h2><br>
</div>

<div class="card">
  <h1>LED 03</h1><br>
  <h2>Status <span id="Variavel03">0</span></h2><br>
  <h2>On-Off</h2><br>
</div>

<script>

setInterval(function(){getData();}, 1000);// Chama a função repetidamente uma vez a cada 1 segundo

function getData() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("Variavel01").innerHTML = this.responseText;
      document.getElementById("Variavel02").innerHTML = this.responseText;
	  document.getElementById("Variavel03").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "LerVariavel01", true);
  xhttp.open("GET", "LerVariavel02", true);
  xhttp.open("GET", "LerVariavel03", true);
  xhttp.send();
}
</script>
</body>
</html>
)=====";
