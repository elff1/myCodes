<?php
$this->breadcrumbs=array(
	ResourceModule::t('resHomework', 'Homeworks')=>array('index'),
	ResourceModule::t('resHomework', 'Create'),
);

$cid = $ass_model->teachingclass_id;
if (isset($_GET['teachingclass_id'])) {
    $cid = $_GET['teachingclass_id'];
}

$this->menu=array(
	array('label'=>ResourceModule::t('resHomework', 'List ResHomework'), 'url'=>array('index', 'teachingclass_id'=>$cid)),
	array('label'=>ResourceModule::t('resHomework', 'Manage ResHomework'), 'url'=>array('admin', 'teachingclass_id'=>$cid)),
);
?>

<h1>Create ResHomework</h1>

<?php echo $this->renderPartial('_form', array('model'=>$model,
    'res_model'=>$res_model)); ?>
