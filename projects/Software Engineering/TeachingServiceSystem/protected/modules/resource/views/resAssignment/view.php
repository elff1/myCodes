<?php
$this->breadcrumbs=array(
	ResourceModule::t('resAssignment', 'Assignments')=>array('index'),
	$model->id,
);

$cid = $model->teachingclass_id;
// show different menu to different kind of user
$u_type = Yii::app()->user->type;
if ($u_type != UserAuthentication::TYPE_STUDENT) {
$this->menu=array(
	array('label'=>ResourceModule::t('resAssignment', 'List Assignment'), 'url'=>array('index', 'teachingclass_id'=>$cid)),
	array('label'=>ResourceModule::t('resAssignment', 'Create Assignment'), 'url'=>array('create', 'teachingclass_id'=>$cid)),
	array('label'=>ResourceModule::t('resAssignment', 'Update Assignment'), 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>ResourceModule::t('resAssignment', 'Delete Assignment'), 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>ResourceModule::t('resAssignment', 'Manage Assignment'), 'url'=>array('admin', 'teachingclass_id'=>$cid)),
);
} else {
    $this->menu=array(
	array('label'=>ResourceModule::t('resAssignment', 'List Assignment'), 'url'=>array('index', 'teachingclass_id'=>$cid)),
);
}
?>

<h1>View ResAssignment #<?php echo $model->id; ?></h1>

<?php $this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'teachingclass_id',
		'resource_id',
		'dead_line',
		'is_published',
		'teacher_id',
        //'requirement',
        array(
            'label'=>ResourceModule::t('resAssignment', 'Requirement'),
            'type'=>'raw',
            'value'=>$model->requirement,
        ),
        array(
            'label'=>ResourceModule::t('resAssignment', 'Download'),
            'type'=>'raw',
            'value'=>"<a href='/protected/uploads/res/"
            .strval($res_model->uploader_id).'+'.$res_model->path."'>".ResourceModule::t('resAssignment', 'Click here')."</a>",
        ),
	),
)); ?>
