<?php
$this->breadcrumbs=array(
	'Class Teachers'=>array('index'),
	$model->id=>array('view','id'=>$model->id),
	'Update',
);

$this->menu=array(
	array('label'=>'List ClassTeacher', 'url'=>array('index')),
	array('label'=>'Create ClassTeacher', 'url'=>array('create')),
	array('label'=>'View ClassTeacher', 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>'Manage ClassTeacher', 'url'=>array('admin')),
);
?>

<h1>Update ClassTeacher <?php echo $model->id; ?></h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>