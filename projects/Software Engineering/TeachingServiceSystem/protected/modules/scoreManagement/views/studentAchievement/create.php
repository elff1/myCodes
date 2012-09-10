<?php
$this->breadcrumbs=array(
	'Student Achievements'=>array('index'),
	'Create',
);

$this->menu=array(
	array('label'=>'List StudentAchievement', 'url'=>array('index')),
	array('label'=>'Manage StudentAchievement', 'url'=>array('admin')),
);
?>

<h1>Create StudentAchievement</h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>