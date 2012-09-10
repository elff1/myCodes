<?php
$this->breadcrumbs=array(
	ResourceModule::t('resAssignment', 'Assignments')=>array('index'),
	ResourceModule::t('resAssignment', 'Create'),
);
// load cid
$cid = $model->teachingclass_id;
if (isset($_GET['teachingclass_id'])) {
    $cid = $_GET['teachingclass_id'];
}

$this->menu=array(
	array('label'=>ResourceModule::t('resAssignment', 'List Assignment'), 'url'=>array('index', 'teachingclass_id'=>$cid)),
	array('label'=>ResourceModule::t('resAssignment', 'Manage Assignment'), 'url'=>array('admin', 'teachingclass_id'=>$cid)),
);
?>

<h1>Create ResAssignment</h1>

<?php echo $this->renderPartial('_form', array('model'=>$model,
    'res_model'=>$res_model)); ?>
