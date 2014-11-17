# Обитель котиков

<a href="http://www.nps.gov/glba/naturescience/harbor-seal-population-monitoring.htm"><img src="http://i.imgur.com/zx5FDP2.jpg"></a>

### Описание файлов:

* `resources/terrain-tiles.png` - набор тайлов размером 32×32 для отрисовки местности. Другие файлы ссылаются на эти тайлы по их порядковому номеру, нумерация начинается с нуля и идет слева направо.
* `resources/terrain-tiles-walkable.json` - массив в формате JSON, описывающий какие тайлы проходимы (1), а какие нет (0). В массиве столько же чисел, сколько тайлов содержится в `terrain-tiles.png`.
* `resources/terrain-map.json` - карта местности в формате JSON. `width`, `height` - ширина и высота карты в тайлах, `tiles` - одномерный массив с индексами тайлов, полученный из двухмерного склейкой строк.