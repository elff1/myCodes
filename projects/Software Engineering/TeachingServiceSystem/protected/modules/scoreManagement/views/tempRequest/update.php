<?php
$this->breadcrumbs=array(
	'Temp Requests'=>array('index'),
	$model->id=>array('view','id'=>$model->id),
	'Update',
);

$this->menu=array(
	array('label'=>'List TempRequest', 'url'=>array('index')),
	array('label'=>'Create TempRequest', 'url'=>array('create')),
	array('label'=>'View TempRequest', 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>'Manage TempRequest', 'url'=>array('admin')),
);
?>

<h1>Update TempRequest <?php echo $model->id; ?></h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>