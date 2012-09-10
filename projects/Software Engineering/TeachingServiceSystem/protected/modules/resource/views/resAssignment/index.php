<?php
$this->breadcrumbs=array(
	ResourceModule::t('resAssignment', 'Assignments'),
);

$cid = null;
if (isset($_GET['teachingclass_id'])) {
    $cid = $_GET['teachingclass_id'];
}
// show different menu
if (Yii::app()->user->type != UserAuthentication::TYPE_STUDENT) {
$this->menu=array(
	array('label'=>ResourceModule::t('resAssignment', 'Create Assignment'), 'url'=>array('create', 'teachingclass_id'=>$cid)),
	array('label'=>ResourceModule::t('resAssignment', 'Manage Assignment'), 'url'=>array('admin', 'teachingclass_id'=>$cid)),
);
}
?>

<h1><?php echo ResourceModule::t('resAssignment', 'Assignments'); ?></h1>

<?php $this->widget('zii.widgets.CListView', array(
	'dataProvider'=>$dataProvider,
	'itemView'=>'_view',
    'sortableAttributes' => array(
        'dead_line' => ResourceModule::t('resAssignment', 'Dead Line'),
    ),
)); ?>
