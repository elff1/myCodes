<?php
$this->breadcrumbs=array(
	'Classroom Basic Infos'=>array('index'),
	$model->id=>array('view','id'=>$model->id),
	'Update',
);

$this->menu=array(
	array('label'=>'List ClassroomBasicInfo', 'url'=>array('index')),
	array('label'=>'Create ClassroomBasicInfo', 'url'=>array('create')),
	array('label'=>'View ClassroomBasicInfo', 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>'Manage ClassroomBasicInfo', 'url'=>array('admin')),
);
?>

<h1>Update ClassroomBasicInfo <?php echo $model->id; ?></h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>