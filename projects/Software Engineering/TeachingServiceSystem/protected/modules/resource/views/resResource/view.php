<?php
$this->breadcrumbs=array(
	ResourceModule::t('resResource','Res Resources')=>array('index', 'uid'=>Yii::app()->user->id),
	$model->id,
);

//allow resouce owner to update, delete, his/her resources.
if ($model->uploader_id == Yii::app()->user->id)
{
$this->menu=array(
	array('label'=>ResourceModule::t('resResource','List ResResource'), 'url'=>array('index', 'uid'=>Yii::app()->user->id)),
	array('label'=>ResourceModule::t('resResource','Create ResResource'), 'url'=>array('create')),
	array('label'=>ResourceModule::t('resResource','Update ResResource'), 'url'=>array('update', 'id'=>$model->id)),
	array('label'=>ResourceModule::t('resResource','Delete ResResource'), 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>ResourceModule::t('resResource','Manage ResResource'), 'url'=>array('admin', 'uid'=>Yii::app()->user->id)),
	array('label'=>ResourceModule::t('resResource','Download ResResource'), 'url'=>array('download', 'id'=>$model->id, 'uid'=>Yii::app()->user->id), 'linkOptions'=>array('target'=>'_blank'))
	);
}
else 
{
$this->menu=array(
	array('label'=>ResourceModule::t('resResource','List ResResource'), 'url'=>array('index', 'uid'=>Yii::app()->user->id)),
	array('label'=>ResourceModule::t('resResource','Create ResResource'), 'url'=>array('create')),
	//array('label'=>'Update ResResource', 'url'=>array('update', 'id'=>$model->id)),
	//array('label'=>'Delete ResResource', 'url'=>'#', 'linkOptions'=>array('submit'=>array('delete','id'=>$model->id),'confirm'=>'Are you sure you want to delete this item?')),
	array('label'=>ResourceModule::t('resResource','Manage ResResource'), 'url'=>array('admin', 'uid'=>Yii::app()->user->id)),
	array('label'=>ResourceModule::t('resResource','Download ResResource'), 'url'=>array('download', 'id'=>$model->id, 'uid'=>Yii::app()->user->id), 'linkOptions'=>array('target'=>'_blank'))
	);
}
?>

<h1>View ResResource #<?php echo $model->id; ?></h1>

<?php $this->widget('zii.widgets.CDetailView', array(
	'data'=>$model,
	'attributes'=>array(
		'id',
		'path',
		'display_name',
		'uploader_id',
		'download_count',
		'resource_type',
		'description',
		'upload_time',
	),
	)
); ?>

<?php 
 	echo '<h1>';
 	echo ResourceModule::t('resResource','comments');
 	echo '</h1>';
?>
 
<?php $this->renderPartial('comment.views.comment.commentList', array('model'=>$model)); ?>

