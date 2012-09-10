<?php
$this->breadcrumbs=array(
	'Student Achievements'=>array('index'),
	$model->id=>array('view','id'=>$model->id),
	'Update',
);

$this->menu=array(
	array('label'=>'List StudentAchievement', 'url'=>array('index')),
	array('label'=>'Create StudentAchievement', 'url'=>array('create')),
	array('label'=>'View StudentAchievement', 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>'Manage StudentAchievement', 'url'=>array('admin')),
);
?>

<h1>Update StudentAchievement <?php echo $model->id; ?></h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>