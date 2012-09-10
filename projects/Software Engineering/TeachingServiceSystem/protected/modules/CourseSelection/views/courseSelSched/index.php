<?php
$this->breadcrumbs=array(
	'Course Sel Scheds',
);

$this->menu=array(
	array('label'=>'Create CourseSelSched', 'url'=>array('create')),
	array('label'=>'Manage CourseSelSched', 'url'=>array('admin')),
);
?>

<h1>Course Sel Scheds</h1>

<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
