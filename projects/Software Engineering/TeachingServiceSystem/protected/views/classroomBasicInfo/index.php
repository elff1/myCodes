<?php
$this->breadcrumbs=array(
	'Classroom Basic Infos',
);

$this->menu=array(
	array('label'=>'Create ClassroomBasicInfo', 'url'=>array('create')),
	array('label'=>'Manage ClassroomBasicInfo', 'url'=>array('admin')),
);
?>

<h1>Classroom Basic Infos</h1>

<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
