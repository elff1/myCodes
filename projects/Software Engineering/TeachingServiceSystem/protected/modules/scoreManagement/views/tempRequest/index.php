<?php
$this->breadcrumbs=array(
	'Temp Requests',
);

$this->menu=array(
	array('label'=>'Create TempRequest', 'url'=>array('create')),
	array('label'=>'Manage TempRequest', 'url'=>array('admin')),
);
?>

<h1>Temp Requests</h1>

<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
