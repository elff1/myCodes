<div class="form">

<?php $form=$this->beginWidget('CActiveForm', array(
	'id'=>'teacher-app-form',
	'enableAjaxValidation'=>false,
)); ?>

	<p class="note">Fields with <span class="required">*</span> are required.</p>

	<?php echo $form->errorSummary($model); ?>
	
	<div class="row">
		<?php echo $form->labelEx($model,'courseID'); ?>
		<?php echo $form->textField($model,'courseID',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'courseID'); ?>
	</div>
	
<!--
	<div class="row">
		<?php echo $form->labelEx($model,'id'); ?>
		<?php echo $form->textField($model,'id'); ?>
		<?php echo $form->error($model,'id'); ?>
	</div>
-->
	<div class="row">
		<?php echo $form->labelEx($model,'preferPlace'); ?>
		<?php echo $form->dropDownList($model, 'preferPlace', array(
		yii::t('courseArrangement', 'yuquan')=>yii::t('courseArrangement', 'yuquan'), 
		yii::t('courseArrangement', 'zijingang')=>yii::t('courseArrangement', 'zijingang'),
		yii::t('courseArrangement', 'xixi')=>yii::t('courseArrangement', 'xixi'),
		
		)
		);?>
		
		<?php echo $form->error($model,'preferPlace'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'preferTime'); ?>
		<?php echo $form->textField($model,'preferTime',array('size'=>45,'maxlength'=>45)); ?>
		<?php echo $form->error($model,'preferTime'); ?>
	</div>

	
<!--
	<div class="row">
		<?php echo $form->labelEx($model,'name'); ?>
		<?php echo $form->textField($model,'name',array('size'=>45,'maxlength'=>45)); ?>
		<?php echo $form->error($model,'name'); ?>
	</div>
-->
	
<!--
	<div class="row">
		<?php echo $form->labelEx($model,'teacherID'); ?>
		<?php echo $form->textField($model,'teacherID',array('size'=>11,'maxlength'=>11)); ?>
		<?php echo $form->error($model,'teacherID'); ?>
	</div>

	<div class="row">
		<?php echo $form->labelEx($model,'appTime'); ?>
		<?php echo $form->textField($model,'appTime'); ?>
		<?php echo $form->error($model,'appTime'); ?>
	</div>
-->
	<div class="row buttons">
		<?php echo CHtml::submitButton($model->isNewRecord ? 'Create' : 'Save'); ?>
	</div>
<?php 
//$course = CourseBasicInfo::model()->getCourseList('123456');
//print_r($course);
//echo($course['123456']);
?>
<?php $this->endWidget(); ?>

</div><!-- form -->