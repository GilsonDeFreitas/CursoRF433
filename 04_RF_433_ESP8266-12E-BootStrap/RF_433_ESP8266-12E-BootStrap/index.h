const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="pt-br">

<head>
<meta charset = "utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css">
  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
  <script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.16.0/umd/popper.min.js"></script>
  <script src="https://maxcdn.bootstrapcdn.com/bootstrap/4.4.1/js/bootstrap.min.js"></script>
</head>

<body>
<div class="container">
  <h2>Monitoramento</h2>
  <div class="card">
    <div class="card-body">
      <h1>Contagem</h1><br>
      <h2>Nr.: <span id="VarContagem">0</span> C</h2><br>
      <h2>Informações adicionais da temperaruta</h2><br>
    </div>
  </div>
  <br>
  <div class="card bg-primary text-white">
    <div class="card-body">
      <h1>LED 01</h1><br>
      <h2>Status: <b><span id="Variavel01">0</span></b> </h2><br>
      <h2>On-Off</h2><br>
    </div>
  </div>
  <br>
  <div class="card bg-success text-white">
    <div class="card-body">
      <h1>LED 02</h1><br>
      <h2>Status:  <b><span id="Variavel02">0</span></b> </h2><br>
      <h2>On-Off</h2><br>
    </div>
  </div>  
  <br>
  <div class="card bg-warning text-white">
    <div class="card-body">
      <h1>LED 03</h1><br>
      <h2>Status:  <b><span id="Variavel03">0</span></b> </h2><br>
      <h2>On-Off</h2><br>
    </div>
  </div>  
</div>

<script>

setInterval(function() { getContagem(); }, 1000); // Chama a função a cada 2000 milisegundos - 2 segundos
function getContagem()
{
  var xhttp = new XMLHttpRequest(); xhttp.onreadystatechange = function()
  {
    if (this.readyState == 4 && this.status == 200)
    {
      document.getElementById("VarContagem").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "LerContagem", true);
  xhttp.send();
}

setInterval(function() { getVariavel01(); }, 1000); // Chama a função a cada 2000 milisegundos - 2 segundos
function getVariavel01()
{
  var xhttp = new XMLHttpRequest(); xhttp.onreadystatechange = function()
  {
    if (this.readyState == 4 && this.status == 200)
    {
      document.getElementById("Variavel01").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "LerVariavel01", true);
  xhttp.send();
}

setInterval(function() { getVariavel02(); }, 1000); // Chama a função a cada 2000 milisegundos - 2 segundos
function getVariavel02()
{
  var xhttp = new XMLHttpRequest(); xhttp.onreadystatechange = function()
  {
    if (this.readyState == 4 && this.status == 200)
    {
      document.getElementById("Variavel02").innerHTML = this.responseText;
      document.getElementById("Variavel03").innerHTML = this.responseText;      
    }
  };
  xhttp.open("GET", "LerVariavel02", true);
  xhttp.open("GET", "LerVariavel03", true);
  xhttp.send();
}

setInterval(function() { getVariavel03(); }, 1000); // Chama a função a cada 2000 milisegundos - 2 segundos
function getVariavel03()
{
  var xhttp = new XMLHttpRequest(); xhttp.onreadystatechange = function()
  {
    if (this.readyState == 4 && this.status == 200)
    {
      document.getElementById("Variavel03").innerHTML = this.responseText;      
    }
  };
  xhttp.open("GET", "LerVariavel03", true);
  xhttp.send();
}

</script>
</body>
</html>
)=====";
