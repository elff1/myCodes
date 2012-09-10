<?php
$this->breadcrumbs=array(
	ResourceModule::t('resHomework', 'Homeworks'),
);
$cid = null;
if (isset($_GET['teachingclass_id'])) {
    $cid = $_GET['teachingclass_id'];
}
// show different menu to different kinds of users
if (Yii::app()->user->type != UserAuthentication::TYPE_STUDENT) {
$this->menu=array(
	//array('label'=>'Create ResHomework', 'url'=>array('create')),
	array('label'=>ResourceModule::t('resHomework', 'Manage Homework'), 'url'=>array('admin', 'teachingclass_id'=>$cid)),
);
}
?>

<h1>Res Homeworks</h1>

<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
)); ?>
