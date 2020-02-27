var map = new L.Map("oMeuMapa1", {center: [40.633258,-8.659097],zoom: 2});
var osmUrl="http://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png";
var osmAttrib="Map data OpenStreetMap contributors";
var osm = new L.TileLayer(osmUrl, {attribution: osmAttrib});
map.addLayer(osm);

var pontos = [
  L.marker([35.15225248, 38.671875]),
  L.marker([35.15225248, 38.671875]).bindPopup("<b>MÉDIO ORIENTE</b><p>Os interesses são principalmente políticos. A disputa é pela posse da terra. Os palestinos consideram que o território ocupado por Israel lhes pertence por direito.</p><p> Além disso, Israel é o único país muçulmano, no Médio Oriente, logo claramente se destaca por ser “diferente” ou “invasor”.</p>"),
  L.marker([49.59362142, 10.37109375]),
  L.marker([49.59362142, 10.37109375]).bindPopup("<b>EUROPA</b><p>Causas principalmente económicas e idealistas. Movimentos extremistas pensam que a violência é necessária para derrubar o capitalismo.</p>"),
  L.marker([-5.64222612, -60.64453125]),
  L.marker([-5.64222612, -60.64453125]).bindPopup("<b>AMÉRICA LATINA</b><p>Produto do conflito entre classes. Até há pouco tempo, quase todas as nações da América Latina eram controladas por regimes corruptos e autoritários, vivendo a maioria das pessoas na pobreza.</p><p> A força impulsionadora deste terrorismo é o desejo de reorganizar a sociedade, retirar os interesses das empresas estrangeiras e redistribuir a terra e a riqueza.</p>")

];

for(i in pontos) { pontos[i].addTo(map); }
