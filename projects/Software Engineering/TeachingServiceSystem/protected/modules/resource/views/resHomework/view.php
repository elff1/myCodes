<?php
$cid = $model->teachingclass_id;
$this->breadcrumbs=array(
	ResourceModule::t('resHomework', 'Homeworks')=>array('index', 'teachingclass_id'=>$cid),
	$model->id,
);
// show different menu
if (Yii::app()->user->type != UserAuthentication::TYPE_STUDENT) {
$this->menu=array(
	array('label'=>ResourceModule::t('resHomework', 'List Homework'), 'url'=>array('index', 'assignment_id'=>$model->assignment_id, 'teachingclass_id'=>$cid)),
	//array('label'=>'Create Homework', 'url'=>array('create')),
	array('label'=>ResourceModule::t('resHomework', 'Update Homework'), 'url'=>array('update', 'id'=>$model->id, 'teachingclass_id'=>$cid)),
	array('label'=>ResourceModule::t('resHomework', 'Delete Homework'), 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>ResourceModule::t('resHomework', 'Manage Homework'), 'url'=>array('admin', 'teachingclass_id'=>$cid, 'assignment_id'=>$model->assignment_id)),
);
} else {
    $this->menu=array(
	array('label'=>ResourceModule::t('resHomework', 'List Homework'), 'url'=>array('index', 'teachingclass_id'=>$cid)),
	//array('label'=>'Create Homework', 'url'=>array('create')),
	array('label'=>ResourceModule::t('resHomework', 'Update Homework'), 'url'=>array('update', 'id'=>$model->id, 'teachingclass_id'=>$cid)),
);
}
?>

<h1>View ResHomework #<?php echo $model->id; ?></h1>

<?php 
$res = ResResource::model()->findbyPk($model->resource_id);
$score = 0;
if ($model->score == -1) {
    $score = 'Not graded';
} else {
    $score = $model->score;
}
$this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'student_id',
        //'score',
        array (
            'label'=>ResourceModule::t('resHomework', 'Score'),
            'type' => 'raw',
            'value' => $score,
        ), 
		'assignment_id',
		'teachingclass_id',
        'submit_time',
        //'comments',
        array(
            'label'=>ResourceModule::t('resHomework', 'Comments'),
            'type'=>'raw',
            'value'=>$model->comments,
        ),
		'resource_id',
        array(
            'label'=>ResourceModule::t('resHomework', 'Description'),
            'type'=>'raw',
            'value'=>$res_model->description,
        ),
        array(
            'label'=>ResourceModule::t('resHomework', 'Download'),
            'type'=>'raw',
            'value'=> CHtml::link(ResourceModule::t('resHomework', 'Click Here'), '/protected/uploads/res/'.strval($res->uploader_id).'+'.$res->path),
        ),
	),
)); ?>
