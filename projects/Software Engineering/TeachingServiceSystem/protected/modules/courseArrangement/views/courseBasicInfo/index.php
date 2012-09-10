<?php
$this->breadcrumbs=array(
	'Course Basic Infos',
);

$this->menu=array(
	array('label'=>'Create CourseBasicInfo', 'url'=>array('create')),
	array('label'=>'Manage CourseBasicInfo', 'url'=>array('admin')),
);
?>

<h1>Course Basic Infos</h1>

<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
