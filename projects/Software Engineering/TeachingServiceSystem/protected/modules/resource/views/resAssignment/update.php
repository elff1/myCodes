<?php
$this->breadcrumbs=array(
	ResourceModule::t('resAssignment', 'Assignments')=>array('index'),
	$model->id=>array('view','id'=>$model->id),
	ResourceModule::t('resAssignment', 'Update'),
);

$cid = $model->teachingclass_id;

$this->menu=array(
	array('label'=>ResourceModule::t('resAssignment', 'List Assignment'), 'url'=>array('index', 'teachingclass_id'=>$cid)),
	array('label'=>ResourceModule::t('resAssignment', 'Create Assignment'), 'url'=>array('create', 'teachingclass_id'=>$cid)),
	array('label'=>ResourceModule::t('resAssignment', 'View Assignment'), 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>ResourceModule::t('resAssignment', 'Manage Assignment'), 'url'=>array('admin', 'teachingclass_id'=>$cid)),
);
?>

<h1>Update ResAssignment <?php echo $model->id; ?></h1>

<?php echo $this->renderPartial('_form', array('model'=>$model,
    'res_model'=>$res_model)); ?>
