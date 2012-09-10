<?php
$this->breadcrumbs=array(
	'Teacher Apps'=>array('index'),
	$model->name=>array('view','id'=>$model->id),
	'Update',
);

$this->menu=array(
	array('label'=>'List TeacherApp', 'url'=>array('index')),
	array('label'=>'Create TeacherApp', 'url'=>array('create')),
	array('label'=>'View TeacherApp', 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>'Manage TeacherApp', 'url'=>array('admin')),
);
?>

<h1>Update TeacherApp <?php echo $model->id; ?></h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>