<?php
$this->breadcrumbs=array(
	'Classroom Basic Infos'=>array('index'),
	'Create',
);

$this->menu=array(
	array('label'=>'List ClassroomBasicInfo', 'url'=>array('index')),
	array('label'=>'Manage ClassroomBasicInfo', 'url'=>array('admin')),
);
?>

<h1>Create ClassroomBasicInfo</h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>