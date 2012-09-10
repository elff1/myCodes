<?php
$this->breadcrumbs=array(
	'Temp Scores'=>array('index'),
	$model->id=>array('view','id'=>$model->id),
	'Update',
);

$this->menu=array(
	array('label'=>'List TempScore', 'url'=>array('index')),
	array('label'=>'Create TempScore', 'url'=>array('create')),
	array('label'=>'View TempScore', 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>'Manage TempScore', 'url'=>array('admin')),
);
?>

<h1>Update TempScore <?php echo $model->id; ?></h1>

<?php echo $this->renderPartial('_form', array('model'=>$model)); ?>