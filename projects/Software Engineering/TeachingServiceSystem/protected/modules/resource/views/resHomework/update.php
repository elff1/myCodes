<?php
$cid = $model->teachingclass_id;
$aid = $model->assignment_id;
$this->breadcrumbs=array(
	ResourceModule::t('resHomework', 'Homeworks')=>array('index', 'teachingclass_id'=>$cid, 'assignment_id'=>$aid),
	$model->id=>array('view','id'=>$model->id),
	'Update',
);
// shiow different menu
if (Yii::app()->user->type != UserAuthentication::TYPE_STUDENT) {
$this->menu=array(
	array('label'=>ResourceModule::t('resHomework', 'List Homework'), 'url'=>array('index', 'assignment_id'=>$model->assignment_id, 'teachingclass_id'=>$cid)),
	//array('label'=>'Create ResHomework', 'url'=>array('create')),
	array('label'=>ResourceModule::t('resHomework', 'View Homework'), 'url'=>array('view', 'id'=>$model->id)),
	array('label'=>ResourceModule::t('resHomework', 'Manage Homework'), 'url'=>array('admin', 'teachingclass_id'=>$model->teachingclass_id)),
);
} else {
    $this->menu=array(
	array('label'=>ResourceModule::t('resHomework', 'List Homework'), 'url'=>array('index', 'teachingclass_id'=>$model->teachingclass_id)),
	//array('label'=>'Create ResHomework', 'url'=>array('create')),
	array('label'=>ResourceModule::t('resHomework', 'View Homework'), 'url'=>array('view', 'id'=>$model->id)),
);
}
?>

<h1>Update ResHomework <?php echo $model->id; ?></h1>

<?php echo $this->renderPartial('_form', array('model'=>$model,
    'res_model'=>$res_model)); ?>
