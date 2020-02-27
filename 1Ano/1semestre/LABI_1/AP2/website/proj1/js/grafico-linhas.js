function desenhaGrafico() {
  $("#grafico-linhas").highcharts({
    title: { text: "Dependência da <i>Internet</i>", },
    xAxis: { categories: ["2010", "2011", "2012", "2013", "2014", "2015"] },
    series: [{ name: "União Europeia", data: [73, 75, 77, 79, 82, 83] }]
  });
};
