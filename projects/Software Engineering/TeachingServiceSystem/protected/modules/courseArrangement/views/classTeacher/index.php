<?php
$this->breadcrumbs=array(
	'Class Teachers',
);

$this->menu=array(
	array('label'=>'Create ClassTeacher', 'url'=>array('create')),
	array('label'=>'Manage ClassTeacher', 'url'=>array('admin')),
);
?>

<h1>Class Teachers</h1>

<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
