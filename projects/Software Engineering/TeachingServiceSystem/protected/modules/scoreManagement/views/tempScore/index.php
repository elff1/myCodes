<?php
$this->breadcrumbs=array(
	'Temp Scores',
);

$this->menu=array(
	array('label'=>'Create TempScore', 'url'=>array('create')),
	array('label'=>'Manage TempScore', 'url'=>array('admin')),
);
?>

<h1>Temp Scores</h1>

<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
