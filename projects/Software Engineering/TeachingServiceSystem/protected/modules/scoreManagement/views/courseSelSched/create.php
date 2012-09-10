<?php
$this->breadcrumbs=array(
	'Course Sel Scheds'=>array('index'),
	'Create',
);

$this->menu=array(
	array('label'=>'List CourseSelSched', 'url'=>array('index')),
	array('label'=>'Manage CourseSelSched', 'url'=>array('admin')),
);
?>

<h1>Create CourseSelSched</h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>