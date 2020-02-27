var map = new L.Map("oMeuMapa", {center: [40.633258,-8.659097],zoom: 2});
var osmUrl="http://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png";
var osmAttrib="Map data OpenStreetMap contributors";
var osm = new L.TileLayer(osmUrl, {attribution: osmAttrib});
map.addLayer(osm);

var pontos = [
  L.marker([41.381474, 2.1731535]),
  L.marker([41.381474, 2.1731535]).bindPopup("<b>BARCELONA, Espanha</b> 18 de agosto de 2017 <p>Uma carrinha subiu o pavimento e conduziu contra a multidão que passeava pela famosa avenida Las Ramblas.</p><p>13 pessoas foram mortas e mais de uma centena ficou ferida.</p>"),
  L.marker([40.7127753, -74.0059728]),
  L.marker([40.7127753, -74.0059728]).bindPopup("<b>NOVA IORQUE, Estados Unidos da América</b> 31 de outubro de 2017 <p>Carrinha alugada circulou em contramão por uma via partilhada por peões e ciclistas na Baixa de Manhattan e atingiu várias pessoas. Colidiu ainda com um autocarro escolar.</p><p>Oito pessoas morreram e mais de uma dezena acabaram feridos.</p>"),
  L.marker([53.4807593, -2.2426305]),
  L.marker([53.4807593, -2.2426305]).bindPopup("<b>MANCHESTER, Inglaterra</b> 22 de maio de 2017<p>Um <i>homem-bomba</i> detonou explosivos no meio de um concerto da cantora Ariana Grande, na Manchester Arena.</p><p>O ataque terrorista matou pelo menos 22 pessoas e feriu 59.</p>"),
  L.marker([59.9342802, 30.3350986]),
  L.marker([59.9342802, 30.3350986]).bindPopup("<b>SÃO PETERSBURGO, Rússia</b> 3 de abril de 2017<p>Explosão numa carruagem do metro de São Petersburgo. Foi encontrado e desativado um segundo explosivo de fabrico caseiro numa outra estação de metro.</p><p>Morreram 11 pessoas e mais de 40 ficaram feridas.</p>"),
  L.marker([59.3293235, 18.0685808]),
  L.marker([59.3293235, 18.0685808]).bindPopup("<b>ESTOCOLMO, Suécia</b> 7 de abril de 2017<p>Camião acelerou contra multidão numa rua pedonal, tendo depois colidido com o edifício de um centro comercial.</p><p>4 pessoas mortas e, pelo menos 15 feridas.</p>"),
  L.marker([51.5008638, -0.1219645]),
  L.marker([51.5008638, -0.1219645]).bindPopup("<b>LONDRES, Inglaterra</b> 3 de junho de 2017<p>Veículo atinge peões na London Bridge, continuando depois para Borough Market.</p><p>Resultou em 7 mortos e 48 feridos.</p>"),
  L.marker([48.8657844, 2.3073141]),
  L.marker([48.8657844, 2.3073141]).bindPopup("<b>PARIS, França</b> 21 de abril de 2017<p>Polícia foi morto e dois outros ficaram gravemente feridos, após tiroteio no meio da avenida.</p><p> ISIS, conhecido grupo terrorista, assumiu a responsabilidade do ato.</p> "),
  L.marker([31.0248898, 33.0093079]),
  L.marker([31.0248898, 33.0093079]).bindPopup("<b>BIR AL-ABED, Egito</b> 24 de novembro de 2017 <p>Atentado em massa resultante de bombas e armas de fogo na mesquita Al Radwah, no dia de <i>Jumu'ah</i></p><p>Contaram-se 305 mortes e 109 feridos.</p>"),
  L.marker([41.044, 29.002]),
  L.marker([41.044, 29.002]).bindPopup("<b>BESIKTAS, Turquia</b> 1 de janeiro de 2017 <p>Tiroteio em massa numa discoteca em Besiktas onde se celebrava a passagem de ano.</p><p>Morreram pelo menos 39 pessoas e 69 ficaram feridas.</p>")
];

for(i in pontos) { pontos[i].addTo(map); }
