<?php
$this->breadcrumbs=array(
	'Online Test Subsystem'=>array('/testOnline'),
	'Paper Bank'=>array('paperBank/'),
//	'Papers'=>array('index'),
	$model->id=>array('view','id'=>$model->id),
	'Update',
);

$this->menu=array(
	array('label'=>'List Paper', 'url'=>array('index')),
	array('label'=>'Create Paper', 'url'=>array('create')),
	array('label'=>'View Paper', 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>'Manage Paper', 'url'=>array('admin')),
);
?>

<h1>Update Paper <?php echo $model->id; ?></h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>