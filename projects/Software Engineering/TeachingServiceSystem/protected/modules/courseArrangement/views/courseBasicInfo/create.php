<?php
$this->breadcrumbs=array(
	'Course Basic Infos'=>array('index'),
	'Create',
);

$this->menu=array(
	array('label'=>'List CourseBasicInfo', 'url'=>array('index')),
	array('label'=>'Manage CourseBasicInfo', 'url'=>array('admin')),
);
?>

<h1>Create CourseBasicInfo</h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>